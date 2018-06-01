#ifndef SCHED_CLASS_H
#define SCHED_CLASS_H

class SchedClass {
	
	public:

		const SchedClass *next;

		virtual void enqueue_task(struct rq *rq, struct task_struct *p, 
								  int wakeup, bool head) = 0;

		virtual void dequeue_task(struct rq *rq, struct task_struct *p, 
								  int sleep) = 0;
		
		virtual void yield_task(struct rq *rq) = 0;
		
		virtual void check_preempt_curr(struct rq *rq, struct task_struct *p,
										int flags) = 0;
		
		virtual task_struct* pick_next_task(struct rq *rq) = 0;
		
		virtual void put_prev_task(struct rq *rq, struct task_struct *p) = 0;
};

class FairSchedClass : public SchedClass {
	
	public:

		FairSchedClass();

		void enqueue_task(struct rq *rq, struct task_struct *p, int wakeup,
						  bool head);

		void dequeue_task(struct rq *rq, struct task_struct *p, int sleep);
		
		void yield_task(struct rq *rq);
		
		void check_preempt_curr(struct rq *rq, struct task_struct *p, 
								int flags);
		
		task_struct* pick_next_task(struct rq *rq);
		
		void put_prev_task(struct rq *rq, struct task_struct *p);

};

#endif
