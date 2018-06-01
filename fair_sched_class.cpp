#include "sched_class.h"

FairSchedClass::FairSchedClass() {
	this->next = nullptr;
}

void FairSchedClass::enqueue_task(struct rq *rq, struct task_struct *p, 
								  int wakeup, bool head) {

}

void FairSchedClass::dequeue_task(struct rq *rq, struct task_struct *p, 
								  int sleep){}

void FairSchedClass::yield_task(struct rq *rq){}

void FairSchedClass::check_preempt_curr(struct rq *rq, struct task_struct *p,
										int flags){}

task_struct* FairSchedClass::pick_next_task(struct rq *rq){}

void FairSchedClass::put_prev_task(struct rq *rq, struct task_struct *p){}