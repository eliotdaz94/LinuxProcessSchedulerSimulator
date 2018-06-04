#include "cfs_rq.h"

CFSRunQueue::CFSRunQueue() {
	this->nr_running = 0;
	this->exec_clock = 0;
	this->min_vruntime = 0;
	this->curr = nullptr; 
	this->next = nullptr;
	this->last = nullptr;
	this->nr_spread_over = 0;
	this->task_weight = 0;
	this->h_load = 0;
	this->shares = 0;
	this->rq_weight = 0;
}