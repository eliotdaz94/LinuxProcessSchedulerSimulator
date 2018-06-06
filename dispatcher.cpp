#include <thread>
#include <mutex>
#include <cmath>
#include <iostream>
#include "dispatcher.h"
#include "cpu.h"
#include "cfs_rq.h"
#include "task.h"
#include "sched_entity.h"
#include "rb_node.h"
#include "fair_sched_class.h"
#include "prio.h"

bool check_iddle_cpus(CPU cpus[], int nr_cpus) {
	bool all_iddle = true;
	for (int i = 0; i < nr_cpus; i++) {
		//std::cout << "CPU[" << i << "]: " << (cpus[i].current != nullptr) << std::endl;
		all_iddle = all_iddle && (cpus[i].current == nullptr);
	}
	return all_iddle;
}

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq, bool *exit, 
				std::mutex *write) {
	RedBlackNode *new_node;
	SchedEntity *new_entity;
	Task *new_task;
	Task *prev_task;
	bool finished = false;
	double time_slice;
	int i = 0;
	int j = 0;
	// Falta hacer que esto corra siempre.
	//!finished &&
	//for (int x = 0; x <nr_cpus; x++) {
	while (!finished) {
		if (!cpus[i].occupied) {
			// El CPU esta desocupado pero tenia un task previamente.
			if (cpus[i].current != nullptr) {
				//std::cout << "CPU[" << i << "] esta ocioso. " << "Y tiene un task previo. " << std::endl;
				// Verifica si se ha terminado la rafaga de CPU. En caso 
				// positivo, verifica si el task ha finalizado o si se bloquea
				// para hacer I/O.
				prev_task = cpus[i].current;
				//std::cout << prev_task->requirements[0].use_time << std::endl;
				//std::cout << "if: " << (prev_task->requirements[0].use_time == 0) << std::endl;
				if (prev_task->requirements[0].use_time == 0) {
					prev_task->requirements.erase(prev_task->requirements.begin());
					// No estoy seguro de esto.
					prev_task->se.vruntime = 0;
					prev_task->se.run_node.value = prev_task->se.vruntime;
					if (prev_task->requirements.empty()) {
						prev_task->state = 1;
					}
					else {
						prev_task->state = -1;
					}
				}
				else {
					if (prev_task->se.load.weight == NICE_0_LOAD) {
						prev_task->se.vruntime += cpus[i].time;
						prev_task->se.run_node.value = prev_task->se.vruntime;	
					}
					else {
						prev_task->se.vruntime += cpus[i].time * NICE_0_LOAD / 
												  prev_task->se.load.weight;
						prev_task->se.run_node.value = prev_task->se.vruntime;
					}
				}	
				// El task se encola dependiendo de su estado.
				
				if (prev_task->state == 0) {
					// Se encola en el arbol del CFS.
					write->lock();
					std::cout << "Task con PID " << prev_task->pid 
							  << " encolandose en arbol del CFS." << std::endl;
					write->unlock();
					cfs_rq->dispatcher.lock();
					prev_task->sched_class->enqueue_task(prev_task,0,0);
					cfs_rq->dispatcher.unlock();
				}
				else if (prev_task->state == -1) {
					// Se encola en la cola de espera de I/O.
					//continue;
					write->lock();
					std::cout << "Task con PID " << prev_task->pid 
							  << " encolandose en I/O." << std::endl;
					write->unlock();
				}
				else {
					// Se elimina porque ha finalizado.
					write->lock();
					std::cout << "Task con PID " << prev_task->pid 
							  << " ha finalizado." << std::endl;
					write->unlock();
					delete prev_task;
				}
				cpus[i].current = nullptr;
			}
			// Si hay task listas para corre se selecciona la siguiente.	
			if (cfs_rq->nr_running != 0) {
				//std::cout << "Hay tasks en el arbol del CFS" << std::endl;
				cfs_rq->dispatcher.lock();
				//std::cout << "Dispatcher toma el lock" << std::endl;
				new_node = cfs_rq->tasks_timeline.tree_minimum();
				//std::cout << "Nodo seleccionado: " << new_node->value << std::endl;
				new_entity = new_node->my_entity;
				// Se calcula el time-slice:
				//std::cout << "Targeted latency: " << (double)cfs_rq->target_latency << std::endl;
				//std::cout << "Peso del nodo: " << (double)new_entity->load.weight << std::endl;
				//std::cout << "Peso del arbol: " << (double)cfs_rq->load.weight << std::endl;
				time_slice = (double)cfs_rq->target_latency *
							 (double)new_entity->load.weight /
							 (double)cfs_rq->load.weight;
				//std::cout << "Times slice inicial: " << time_slice << std::endl;
				new_task = new_entity->my_task;
				// Se desencola del arbol.
				new_task->sched_class->dequeue_task(new_task,0);
				cfs_rq->dispatcher.unlock();
				//std::cout << "Dispatcher suelta el lock" << std::endl;
				// Se verifica que el time-slice sea valido:
				if (time_slice < cfs_rq->min_granularity) {
					time_slice = cfs_rq->min_granularity;
				}
				else {
					time_slice = round(time_slice);
				}
				//std::cout << "Mi PID es: " << new_task->pid << std::endl;
				//std::cout << "Lo que le sobra a la rafaga: " << new_task->requirements[0].use_time << std::endl;
				if (new_task->requirements[0].use_time < time_slice) {
					//std::cout << "El time slice es mayor que la rafaga" << std::endl;
					time_slice = new_task->requirements[0].use_time;	
				}
				//std::cout << "Times slice final: " << time_slice << std::endl;
				// Se le asigna por afinidad el CPU.
				cpus[i].occupied = true;
				cpus[i].time = (int)time_slice;
				cpus[i].current = new_task;
				std::thread processing(&CPU::consume_time, &cpus[i], i, write);
				processing.detach();
			}
		}
		//std::cout << "Exit: " << *exit << std::endl;
		if (*exit) {
			//std::cout << "Exit: " << exit << std::endl;
			// Hay que tomar en cuenta que puede haber procesos en la cola I/O.
			//std::cout << "Me han avisado que todo va de salida. Chequeare." << std::endl;
			finished = check_iddle_cpus(cpus, nr_cpus);
			//std::cout << "Todos son CPUs ociosos: " << finished << std::endl;
		}
		i = (i+1) % nr_cpus;
		j++;
	}
}