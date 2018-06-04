#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "task.h"
#include "sched_entity.h"

/*
static inline void update_load_add(struct load_weight *lw, unsigned long inc)
{
	lw->weight += inc;
	lw->load->inv_weight = 0;
}

add_cfs_task_weight(struct cfs_rq *cfs_rq, unsigned long weight)
{
	cfs_rq->task_weight += weight;
}

account_entity_enqueue(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	//update_load_add(&cfs_rq->load, se->load.weight);
	cfs_rq->load->weight += se->load.weight;
	cfs_rq->load->inv_weight = 0;
	
	//if (!parent_entity(se))
	//	inc_cpu_load(rq_of(cfs_rq), se->load.weight);
	//if (entity_is_task(se)) {
		
		//add_cfs_task_weight(cfs_rq, se->load.weight);
		cfs_rq->task_weight += se->load.weight;
		
		//list_add(&se->group_node, &cfs_rq->tasks);
	//}
	cfs_rq->nr_running++;
	se->on_rq = 1;
}
*/

FairSchedClass::FairSchedClass() {
	this->next = nullptr;
}

void FairSchedClass::enqueue_task(CFSRunQueue *cfs_rq, Task *p, int wakeup, 
								  bool head) {
	
	SchedEntity *se = &p->se;
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	//if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATE))
		se->vruntime += cfs_rq->min_vruntime;

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
	cfs_rq->tasks_timeline.insert(&se->run_node);
}

void FairSchedClass::dequeue_task(CFSRunQueue *cfs_rq, Task *p, int sleep){};

void FairSchedClass::yield_task(CFSRunQueue *cfs_rq){};

void FairSchedClass::check_preempt_curr(CFSRunQueue *cfs_rq, Task *p, int flags){};

Task* FairSchedClass::pick_next_task(CFSRunQueue *cfs_rq){};

void FairSchedClass::put_prev_task(CFSRunQueue *cfs_rq, Task *p){};