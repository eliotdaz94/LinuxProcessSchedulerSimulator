#include <thread>
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

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq) {
	RedBlackNode *new_node;
	SchedEntity *new_entity;
	Task *new_task;
	Task *prev_task;
	double time_slice;
	
	// Falta hacer que esto corra siempre.
	for (int i = 0; i < nr_cpus; i++) {
		if (!cpus[i].occupied) {
			std::cout << "CPU[" << i << "] esta ocioso." << std::endl;
			// El CPU esta desocupado pero tenia un task previamente.
			if (cpus[i].current != nullptr) {
				// Verifica si se ha terminado la rafaga de CPU. En caso 
				// positivo, verifica si el task ha finalizado o si se bloquea
				// para hacer I/O.
				prev_task = cpus[i].current;
				if (prev_task->requirements[0].use_time == 0) {
					prev_task->requirements.erase(prev_task->requirements.begin());
					// No estoy seguro de esto.
					prev_task->se.vruntime = 0;
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
					}
					else {
						prev_task->se.vruntime += cpus[i].time * NICE_0_LOAD / 
												  prev_task->se.load.weight;
					}
				}	
				// El task se encola dependiendo de su estado.
				if (prev_task->state = 0) {
					// Se encola en el arbol del CFS.
					cfs_rq->dispatcher.lock();
					prev_task->sched_class->enqueue_task(prev_task,0,0);
					cfs_rq->dispatcher.unlock();
				}
				else if (prev_task->state = -1) {
					// Se encola en la cola de espera de I/O.
					continue;
				}
				else {
					// Se elimina porque ha finalizado.
					delete prev_task;
				}
				cpus[i].current = nullptr;
			}
			// Si hay task listas para corre se selecciona la siguiente.	
			if (cfs_rq->nr_running != 0) {
				std::cout << "Hay tasks en el arbol del CFS" << std::endl;
				cfs_rq->dispatcher.lock();
				std::cout << "Dispatcher toma el lock" << std::endl;
				new_node = cfs_rq->tasks_timeline.tree_minimum();
				std::cout << "Nodo seleccionado: " << new_node->value << std::endl;
				new_entity = new_node->my_entity;
				// Se calcula el time-slice:
				std::cout << "Targeted latency: " << (double)cfs_rq->target_latency << std::endl;
				std::cout << "Peso del nodo: " << (double)new_entity->load.weight << std::endl;
				std::cout << "Peso del arbol: " << (double)cfs_rq->load.weight << std::endl;
				time_slice = (double)cfs_rq->target_latency *
							 (double)new_entity->load.weight /
							 (double)cfs_rq->load.weight;
				std::cout << "Times slice inicial: " << time_slice << std::endl;
				new_task = new_entity->my_task;
				// Se desencola del arbol.
				new_task->sched_class->dequeue_task(new_task,0);
				cfs_rq->dispatcher.unlock();
				std::cout << "Dispatcher suelta el lock" << std::endl;
				// Se verifica que el time-slice sea valido:
				if (time_slice < cfs_rq->min_granularity) {
					time_slice = cfs_rq->min_granularity;
				}
				else {
					time_slice = round(time_slice);
				}
				std::cout << "Times slice final: " << time_slice << std::endl;
				std::cout << "Lo que le sobra a la rafaga: " << new_task->requirements[0].use_time << std::endl;
				std::cout << "Mi PID es: " << new_task->pid << std::endl;
				if (new_task->requirements[0].use_time < time_slice) {
					std::cout << "El time slice es mayor que la rafaga" << std::endl;
					time_slice -= new_task->requirements[0].use_time;	
				}
				// Se le asigna por afinidad el CPU.
				cpus[i].current = new_task;
				cpus[i].time = (int)time_slice;
				std::thread processing(&CPU::consume_time, cpus[i]);
				processing.join();
			}
		}
	}
}