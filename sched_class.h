#ifndef SCHED_CLASS_H
#define SCHED_CLASS_H

#include "cfs_rq.h"
#include "task.h"

class SchedClass {
	
	public:

		const SchedClass *next;

		virtual void enqueue_task() = 0;

		virtual void dequeue_task() = 0;
		
		virtual void yield_task() = 0;
		
		virtual void check_preempt_curr() = 0;
		
		virtual Task* pick_next_task() = 0;
		
		virtual void put_prev_task() = 0;

};

#endif
