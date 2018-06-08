#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "task.h"
#include "sched_entity.h"

FairSchedClass::FairSchedClass(){}

void FairSchedClass::enqueue_task(Task *p, int wakeup, bool head) const {
	
	//cfs_rq->creator
	SchedEntity *se = &(p->se);
	CFSRunQueue *cfs_rq = se->cfs_rq;
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	//if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATE))

	/*
	 * Update run-time statistics of the 'current'.
	 */
	//update_curr(cfs_rq);
	
	//account_entity_enqueue(cfs_rq, se);
	cfs_rq->load.weight += se->load.weight;
	cfs_rq->load.inv_weight = 0;
	cfs_rq->task_weight += se->load.weight;
	cfs_rq->nr_running++;
	se->on_rq = 1;

	//if (flags & ENQUEUE_WAKEUP) {
	//	place_entity(cfs_rq, se, 0);
	//	enqueue_sleeper(cfs_rq, se);
	//}

	//update_stats_enqueue(cfs_rq, se);
	//check_spread(cfs_rq, se);
	//if (se != cfs_rq->curr)
	//	__enqueue_entity(cfs_rq, se);
	cfs_rq->tasks_timeline.insert(&(se->run_node));
}

void FairSchedClass::dequeue_task(Task *p, int sleep) const {
	SchedEntity *se = &(p->se);
	CFSRunQueue *cfs_rq = se->cfs_rq;
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	//if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATE))
	/*
	 * Update run-time statistics of the 'current'.
	 */
	//update_curr(cfs_rq);
	
	//account_entity_enqueue(cfs_rq, se);
	cfs_rq->load.weight -= se->load.weight;
	cfs_rq->load.inv_weight = 0;
	cfs_rq->task_weight -= se->load.weight;
	cfs_rq->nr_running--;
	se->on_rq = 0;
	cfs_rq->tasks_timeline.remove(&(se->run_node));
}