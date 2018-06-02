#ifndef SCHED_ENTITY_H
#define SCHED_ENTITY_H

#include "rb_node.h"
#include "load_weight.h"

class CFSRunQueue;

class SchedEntity {
	public:
		
		//struct load_weight load;		/* for load-balancing */
		LoadWeight load;
		//struct rb_node run_node;
		RedBlackNode run_node;
		//struct list_head group_node;
		unsigned int on_rq;
		long exec_start;
		long sum_exec_runtime;
		long vruntime;
		long prev_sum_exec_runtime;
		long last_wakeup;
		long avg_overlap;
		long nr_migrations;
		long start_runtime;
		long avg_wakeup;
		//#ifdef CONFIG_FAIR_GROUP_SCHED
			//struct sched_entity	*parent;
			/* rq on which this entity is (to be) queued: */
		//cfs_rq		*cfs_rq;
		CFSRunQueue *cfs_rq;
			/* rq "owned" by this entity/group: */
			//struct cfs_rq		*my_q;
		//#endif

		SchedEntity();
};

#endif