#ifndef CFS_RUN_QUEUE
#define CFS_RUN_QUEUE

#include "rb_tree.h"
#include "load_weight.h"

class SchedEntity;

class CFSRunQueue {
	
	public: 
		
		LoadWeight load;
		unsigned long nr_running;

		long exec_clock;
		long min_vruntime;

		RedBlackTree tasks_timeline;
		RedBlackNode *rb_leftmost;

		//struct list_head tasks;
		//struct list_head *balance_iterator;

		/*
		 * 'curr' points to currently running entity on this cfs_rq.
		 * It is set to NULL otherwise (i.e when none are currently running).
		 */
		SchedEntity *curr, *next, *last;

		unsigned int nr_spread_over;

	
	//#ifdef CONFIG_FAIR_GROUP_SCHED
	//	struct rq *rq;	/* cpu runqueue to which this cfs_rq is attached */

		/*
		 * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
		 * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
		 * (like users, containers etc.)
		 *
		 * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a cpu. This
		 * list is used during load balance.
		 */
	//	struct list_head leaf_cfs_rq_list;
	//	struct task_group *tg;	/* group that "owns" this runqueue */

	//#ifdef CONFIG_SMP
		/*
		 * the part of load.weight contributed by tasks
		 */
		unsigned long task_weight;

		/*
		 *   h_load = weight * f(tg)
		 *
		 * Where f(tg) is the recursive weight fraction assigned to
		 * this group.
		 */
		unsigned long h_load;

		/*
		 * this cpu's part of tg->shares
		 */
		unsigned long shares;

		/*
		 * load.weight at the time we set shares
		 */
		unsigned long rq_weight;
	//#endif
	//#endif

		CFSRunQueue();
};

#endif