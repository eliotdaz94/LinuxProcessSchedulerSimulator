#include <thread>
#include <mutex>
#include <cmath>
#include <iostream>
#include "cpu.h"
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

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq, bool *exit, 
				std::mutex *write) {
	Task *prev_task;
	Task *next_task;
	SchedEntity *next_entity;
	RedBlackNode *next_node;
	bool finished = false;
	double time_slice;
	int i = 0;
	while(!finished) {
		//if (cpus[i].occupied.try_lock()) {
		//if (cpus[i].use.try_lock() && !cpus[i].occupied) {
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
					if (prev_task->requirements[0].type == "CPU") {
						prev_task->state = 0;
						write->lock();
						std::cout << "Task con PID " << prev_task->pid 
								  << " encolandose en arbol del CFS: " 
								  << prev_task->requirements[0].use_time  
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
						/* Lo siguiente que hace no es lo correcto */
						//delete prev_task;
					}
				}
				cpus[i].current = nullptr;
			}
			cfs_rq->dispatcher.lock();
			// Tomamos el siguiente nodo listo para ejecutarse, de existir.
			if (cfs_rq->nr_running > 0) {
				//write->lock();
				//std::cout << "SIPEEE GUEY, SI HAY ALGUIEN" << std::endl;
				//write->unlock();
				next_node = cfs_rq->tasks_timeline.tree_minimum();
				
				if (next_node->value == -1) {
					write->lock();
					std::cout << "NODOS: " << cfs_rq->nr_running << std::endl;
					std::cout << "NODOS: " << cfs_rq->tasks_timeline.nodes << std::endl;
					std::cout << "NODO: " << next_node->value << std::endl;
					//cfs_rq->tasks_timeline.print_tree();
					write->unlock();
				} 

				next_entity = next_node->my_entity;
				if (next_entity == nullptr) {
					write->lock();
					std::cout << "AYUUUUURAAA ENTIDAD" << std::endl;
					write->unlock();
				}
				time_slice = (double)cfs_rq->target_latency *
							 (double)next_entity->load.weight /
							 (double)cfs_rq->load.weight;
				//write->lock();
				//std::cout << "CALCULE EL PIZZA SLICE" << std::endl;
				//write->unlock();
				if (next_entity == nullptr) {
					//write->lock();
					//std::cout << "AYUUUUURAAA ENTIDAD" << std::endl;
					//write->unlock();
				}
				
				next_task = next_entity->my_task;
				// Se desencola del arbol.
				next_task->sched_class->dequeue_task(next_task,0);
				write->lock();
				std::cout << "Task con PID " << next_task->pid 
						  << " desencolandose del arbol del CFS : " 
						  << next_task->requirements[0].use_time
						  << std::endl;
				//cfs_rq->tasks_timeline.print_tree();
				cfs_rq->tasks_timeline.in_order();
				//cfs_rq->tasks_timeline.print_tree();
				write->unlock();
				cfs_rq->dispatcher.unlock();
				// Se verifica que el time-slice sea valido:
				if (time_slice < cfs_rq->min_granularity) {
					time_slice = cfs_rq->min_granularity;
				}
				else {
					time_slice = round(time_slice);
				}
				if (next_task->requirements[0].use_time < time_slice) {
					time_slice = next_task->requirements[0].use_time;	
				}
				// Se le asigna por afinidad el CPU.
				//write->lock();
				//std::cout << " PID " << next_task->pid <<" me sobra tiempo: " << next_task->requirements[0].use_time << std::endl;
				//std::cout << "Y me asignan: " << time_slice << std::endl;
				//write->unlock();
				cpus[i].time = (int)time_slice;
				cpus[i].occupied = true;
				cpus[i].current = next_task;
				std::thread processing(&CPU::consume_time, &cpus[i], i, write);
				processing.detach();
			}
			// Verificamos las condiciones de salida del dispatcher.
			else {
				//write->lock();
				//std::cout << "NOOOPE GUEY, NO HAY NADIE" << std::endl;
				//write->unlock();
				cfs_rq->dispatcher.unlock();
				//write->lock();
				//std::cout << "Exit?: " << *exit << std::endl;
				//write->unlock();
				finished = *exit && check_iddle_cpus(cpus, nr_cpus);
				//write->lock();
				//std::cout << "Finalizo?: " << finished << std::endl;
				//write->unlock();
			}
			//Lo ultimo que debo hacer es soltar el lock del CPU actual.
			//cpus[i].use.unlock();
		}
		i = (i + 1) % nr_cpus;
	}
}