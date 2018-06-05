#ifndef SCHED_CLASS_H
#define SCHED_CLASS_H

#include "cfs_rq.h"
#include "task.h"

class SchedClass {
	
	public:

		const SchedClass *next;

		virtual void enqueue_task(Task *p, int wakeup, bool head) const = 0;

		virtual void dequeue_task(Task *p, int sleep) const = 0;
		
		virtual Task* pick_next_task(Task *p) const = 0;
};

#endif