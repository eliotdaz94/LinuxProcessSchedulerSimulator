#include <iostream>
#include "dispatcher.h"
#include "cpu.h"
#include "cfs_rq.h"
#include "task.h"
#include "sched_entity.h"
#include "rb_node.h"

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq) {
	unsigned int time_slice;
	for (int i = 0; i < nr_cpus; i++) {
		if (!cpus[i].occupied) {
			std::cout << "CPU[" << i << "] esta ocioso." << std::endl;
			if (!cpus[i].current) {
				// Calcula lo que tiene que calcular.
				// Lo encola dependiendo del estado.
			}
			if (cfs_rq->nr_running != 0) {
				// Selecciona al siguiente task.
				RedBlackNode *new_node;
				SchedEntity *new_entity;
				Task *new_task;
				cfs_rq->dispatcher.lock();
				new_node = cfs_rq->tasks_timeline.tree_minimum(); 
				new_entity = new_node->my_entity;
				time_slice = cfs_rq->target_latency * new_entity->load.weight 
							 / cfs_rq->load.weight;
				//task_aux->sched_class->enqueue_task(task_aux,0,0);
				cfs_rq->dispatcher.unlock();
				// Le asigna por afinidad el CPU.	
			}
			
		}
	}
}