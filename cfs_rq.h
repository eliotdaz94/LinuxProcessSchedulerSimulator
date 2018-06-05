#ifndef CFS_RUN_QUEUE
#define CFS_RUN_QUEUE

#include <mutex>
#include "rb_tree.h"
#include "load_weight.h"

class SchedEntity;

class CFSRunQueue {
	
	public: 
		
		LoadWeight load;
		unsigned long nr_running;
		RedBlackTree tasks_timeline;
		RedBlackNode *rb_leftmost;
		SchedEntity *curr, *next, *last;
		unsigned long task_weight;
		unsigned int target_latency;
		unsigned int min_granularity;
		std::mutex creator;  
		std::mutex dispatcher;

		CFSRunQueue();
};

#endif