#ifndef TASK_GENERATOR_H
#define TASK_GENERATOR_H

#include <mutex>
#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "threshold.h"

void task_generator(int max_life_time, float nice_probability, 
					float policy_probability, float window_size, 
					FairSchedClass *fair_class, CFSRunQueue *cfs_rq,
					Threshold *thresh, int *nr_task_gen, std::mutex *write);

#endif