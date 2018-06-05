#include "cfs_rq.h"

CFSRunQueue::CFSRunQueue() {
	this->nr_running = 0;
	this->curr = nullptr; 
	this->next = nullptr;
	this->last = nullptr;
	this->task_weight = 0;
	this->target_latency = 20;
	this->min_granularity = 1;
}