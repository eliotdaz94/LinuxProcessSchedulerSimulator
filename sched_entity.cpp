#include "sched_entity.h"
#include "load_weight.h"
#include "rb_node.h"

SchedEntity::SchedEntity() {
	this->run_node.my_entity = this;
	this->on_rq = 0;
	this->exec_start = 0;
	this->sum_exec_runtime = 0;
	this->vruntime = 0;
	this->prev_sum_exec_runtime = 0;
	this->last_wakeup = 0;
	this->avg_overlap = 0;
	this->nr_migrations = 0;
	this->start_runtime = 0;
	this->avg_wakeup = 0;
	this->my_task = nullptr;
	this->cfs_rq = nullptr;
}