#ifndef TASK_H
#define TASK_H

#include "sched_entity.h"
#include "sched_class.h"

/*
class Process {
	public:
		string type;
		int PID;
		int nice;
		int life_time;
		int v_runtime;
		vector<Resource> requirements;
};
*/

class Task {
	//volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	int state;
	int prio, static_prio, normal_prio;
	unsigned int rt_priority;
	//const struct sched_class *sched_class;
	const SchedClass *sched_class;
	//struct sched_entity se;
	SchedEntity se;
	struct sched_rt_entity rt;
	int pid;
	//pid_t pid;
}

#endif