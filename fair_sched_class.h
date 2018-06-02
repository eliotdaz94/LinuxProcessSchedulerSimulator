#ifndef FAIR_SCHED_CLASS_H
#define FAIR_SCHED_CLASS_H

#include "sched_class.h"
#include "cfs_rq.h"
#include "task.h"

class FairSchedClass : public SchedClass {
	
	public:

		FairSchedClass();

		void enqueue_task(CFSRunQueue *cfs_rq, Task *p, int wakeup, bool head);

		void dequeue_task(CFSRunQueue *cfs_rq, Task *p, int sleep);
		
		void yield_task(CFSRunQueue *cfs_rq);
		
		void check_preempt_curr(CFSRunQueue *cfs_rq, Task *p, int flags);
		
		Task* pick_next_task(CFSRunQueue *cfs_rq);
		
		void put_prev_task(CFSRunQueue *cfs_rq, Task *p);

};

#endif