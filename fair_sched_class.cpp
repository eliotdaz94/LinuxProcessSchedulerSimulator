#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "task.h"

FairSchedClass::FairSchedClass() {
	this->next = nullptr;
}

void FairSchedClass::enqueue_task(CFSRunQueue *cfs_rq, Task *p, int wakeup, 
								  bool head) {
	
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	//if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATE))
	//	se->vruntime += cfs_rq->min_vruntime;

	/*
	 * Update run-time statistics of the 'current'.
	 */
	//update_curr(cfs_rq);
	//account_entity_enqueue(cfs_rq, se);

	//if (flags & ENQUEUE_WAKEUP) {
	//	place_entity(cfs_rq, se, 0);
	//	enqueue_sleeper(cfs_rq, se);
	//}

	//update_stats_enqueue(cfs_rq, se);
	//check_spread(cfs_rq, se);
	//if (se != cfs_rq->curr)
	//s;__enqueue_entity(cfs_rq, se);

}

void FairSchedClass::dequeue_task(CFSRunQueue *cfs_rq, Task *p, int sleep){};

void FairSchedClass::yield_task(CFSRunQueue *cfs_rq){};

void FairSchedClass::check_preempt_curr(CFSRunQueue *cfs_rq, Task *p, int flags){};

Task* FairSchedClass::pick_next_task(CFSRunQueue *cfs_rq){};

void FairSchedClass::put_prev_task(CFSRunQueue *cfs_rq, Task *p){};