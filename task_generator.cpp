#include <mutex>
#include <iostream>
#include "task.h"
#include "policies.h"
#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "threshold.h"
#include "prio.h"

void task_generator(int max_life_time, float nice_probability, 
					float policy_probability, float window_size,
					FairSchedClass *fair_class, CFSRunQueue *cfs_rq, 
					Threshold *thresh, int *nr_task_gen, std::mutex *write) {
	Task *task_aux;
	int pid = 0;
	int i = 0; 
	while(i < 50) {
		task_aux = new Task(i, max_life_time, nice_probability, 
						policy_probability, window_size);
		if (thresh->under_threshold(task_aux->lifetime)) {
			if (task_aux->policy == SCHED_NORMAL) {
				write->lock();
				std::cout << "Creando task con PID " << task_aux->pid << ":" 
						  << std::endl;
				std::cout << "  Nice value: " 
						  << PRIO_TO_NICE(task_aux->static_prio) << std::endl;
				std::cout << "  Lifetime value: " << task_aux->lifetime 
						  << std::endl;
				std::cout << "  Requirements: " << std::endl;
				for(int i = 0; i < task_aux->requirements.size(); i++) {
					std::cout << "    " << task_aux->requirements[i].type << " " 
							  << task_aux->requirements[i].use_time << std::endl;
				}
				std::cout << std::endl;
				write->unlock();
				task_aux->sched_class = fair_class;
				task_aux->se.cfs_rq = cfs_rq;
				task_aux->se.my_task = task_aux;
				// Solo prueba */
				task_aux->se.vruntime = task_aux->lifetime;
				task_aux->se.run_node.value = task_aux->se.vruntime;
				/* ----------- */
				task_aux->se.cfs_rq->creator.lock();
				task_aux->se.cfs_rq->dispatcher.lock();
				task_aux->sched_class->enqueue_task(task_aux,0,0);
				task_aux->se.cfs_rq->dispatcher.unlock();
				task_aux->se.cfs_rq->creator.unlock();
				*nr_task_gen = *nr_task_gen + 1;
			}
		} 
		else {
			delete task_aux;
		}
		i++;
	}
}