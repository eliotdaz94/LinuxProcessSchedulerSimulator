#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "sched_entity.h"

class SchedClass;

class Resource {
	
	public:

		std::string type;
		int use_time;
		
		Resource();
		
		Resource(std::string t, int u_t);

		~Resource();
};

class Task {
	
	public:

		//volatile long state;	/* -1 unrunnable, 0 runnable, >0 finished */
		int state;
		int prio, static_prio, normal_prio;
		unsigned int rt_priority;
		
		//const struct sched_class *sched_class;
		const SchedClass *sched_class;
		
		//struct sched_entity se;
		SchedEntity se;
		
		//struct sched_rt_entity rt;
		
		unsigned int policy;
		int cpus_allowed;
		
		bool hard_affinity;

		int pid;
		//pid_t pid;

		// Miembros personalizados. 
		long lifetime;
		std::vector<Resource> requirements;

		Task();

		Task(int pid, int max_life_time, float nice_probability, 
			 float policy_probability, float window_size);

		//~Task();
};

#endif