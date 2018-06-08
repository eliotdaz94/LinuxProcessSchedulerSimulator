#include <thread>
#include <mutex>
#include <cmath>
#include <iostream>
#include "cpu.h"
#include "io_dev.h"
#include "cfs_rq.h"
#include "task.h"
#include "sched_entity.h"
#include "fair_sched_class.h"
#include "rb_node.h"
#include "prio.h"

bool check_iddle_cpus(CPU cpus[], int nr_cpus) {
	bool all_iddle = true;
	int i = 0;
	while(i < nr_cpus && all_iddle) {
		all_iddle = all_iddle && !cpus[i].occupied && cpus[i].current == nullptr;
		i++;
	}
	return all_iddle;
}

bool check_iddle_io_dev(IODev *io_device) {
	bool iddle;
	io_device->use.lock();
	iddle = !io_device->occupied && io_device->wait_queue.empty() 
			&& io_device->current == nullptr;
	io_device->use.unlock();
	return iddle;
}

void dispatcher(CPU cpus[], int nr_cpus, IODev *io_device, CFSRunQueue *cfs_rq, 
				std::mutex *write, bool *exit) {
	Task *prev_task;
	Task *next_task;
	SchedEntity *next_entity;
	RedBlackNode *next_node;
	bool finished = false;
	double time_slice;
	int i = 0;
	while (!finished) {
		if (!cpus[i].occupied) {
			// Si hay un task asociado al CPU, debo encolarlo dependiendo de su
			// proxima rafaga.
			if (cpus[i].current != nullptr) {
				prev_task = cpus[i].current;

				// Calculamos el vruntime pesado del task. 				
				if (prev_task->se.load.weight == NICE_0_LOAD) {
					prev_task->se.vruntime += cpus[i].time;
				}
				else {
					prev_task->se.vruntime += cpus[i].time * NICE_0_LOAD / 
											  prev_task->se.load.weight;
				}
				prev_task->se.run_node.value = prev_task->se.vruntime;

				// Si ya no quedan rafagas, entonces el task ha finalizado su 
				// ejecucion y se elimina. task.state = 1.
				if (prev_task->requirements.empty()) {
					prev_task->state = 1;
					write->lock();
					std::cout << "Task con PID " << prev_task->pid 
						  	  << " ha finalizado su ejecucion." << std::endl;
					write->unlock();
					//delete prev_task;
				}
				else {
					// Si la rafaga actual es de tipo CPU, entonces el task 
					// esta listo para ser ejecutado y se encola de nuevo en el
					//arbol del CFS. task.state = 0.
					if (prev_task->requirements.front().type == "CPU") {
						prev_task->state = 0;
						write->lock();
						std::cout << "Task con PID " << prev_task->pid 
								  << " encolandose en arbol del CFS: " 
								  << prev_task->requirements.front().use_time  
								  << std::endl;
						write->unlock();
						cfs_rq->dispatcher.lock();
						prev_task->sched_class->enqueue_task(prev_task,0,0);
						cfs_rq->dispatcher.unlock();
					}
					// Si la rafaga actual es de tipo I/O, entonces el task 
					// se bloquea y se encola en la cola para dispositivos I/O.
					// task.state = -1.
					else {
						prev_task->state = -1;
						write->lock();
						std::cout << "Task con PID " << prev_task->pid 
								  << " encolandose en I/O." << std::endl;
						write->unlock();
						io_device->use.lock();
						io_device->wait_queue.push_back(prev_task);
						io_device->use.unlock();
					}
				}
				cpus[i].current = nullptr;
			}
			cfs_rq->dispatcher.lock();
			// Tomamos el siguiente nodo listo para ejecutarse, de existir.
			if (cfs_rq->nr_running > 0) {
				next_node = cfs_rq->tasks_timeline.tree_minimum();
				next_entity = next_node->my_entity;
				time_slice = (double)cfs_rq->target_latency *
							 (double)next_entity->load.weight /
							 (double)cfs_rq->load.weight;				
				next_task = next_entity->my_task;
				// Se desencola del arbol.
				next_task->sched_class->dequeue_task(next_task,0);
				write->lock();
				std::cout << "Task con PID " << next_task->pid 
						  << " desencolandose del arbol del CFS : " 
						  << next_task->requirements.front().use_time
						  << std::endl;
				write->unlock();
				cfs_rq->dispatcher.unlock();
				// Se verifica que el time-slice sea valido:
				if (time_slice < cfs_rq->min_granularity) {
					time_slice = cfs_rq->min_granularity;
				}
				else {
					time_slice = round(time_slice);
				}
				if (next_task->requirements.front().use_time < time_slice) {
					time_slice = next_task->requirements.front().use_time;	
				}
				// Se le asigna por afinidad el CPU.
				cpus[i].time = (int)time_slice;
				cpus[i].occupied = true;
				cpus[i].current = next_task;
				std::thread processing(&CPU::consume_time, &cpus[i], i, write);
				processing.detach();
			}
			// Verificamos las condiciones de salida del dispatcher.
			else {
				cfs_rq->dispatcher.unlock();
				finished = *exit && check_iddle_cpus(cpus, nr_cpus) 
						   && check_iddle_io_dev(io_device);
				if (finished) {
					cfs_rq->dispatcher.lock();
					finished = (cfs_rq->nr_running == 0);
					cfs_rq->dispatcher.unlock();
				}
			}
		}
		i = (i + 1) % nr_cpus;
	}
	write->lock();
	std::cout << "Dispatcher terminando ejecucion." << std::endl;
	write->unlock();
}