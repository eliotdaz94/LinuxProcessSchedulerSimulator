#ifndef FAIR_SCHED_CLASS_H
#define FAIR_SCHED_CLASS_H

#include "sched_class.h"
#include "cfs_rq.h"
#include "task.h"

class FairSchedClass : public SchedClass {
	
	public:

		FairSchedClass();

		void enqueue_task(Task *p, int wakeup, bool head) const;

		void dequeue_task(Task *p, int sleep) const;
};

#endif