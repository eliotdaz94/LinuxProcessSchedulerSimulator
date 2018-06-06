#include <string>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include "task.h"
#include "prio.h"
#include "sched_entity.h"
#include "sched_class.h"
#include "policies.h"

Resource::Resource(std::string t, int u_t) {
	this->type = t; 
	this->use_time = u_t;
}

Task::Task(int pid, int max_lifetime, float nice_probability, 
		   float policy_probability, float window_size) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> dist(1,10);		
	int aux;
	int u_t;
	int upper_bound;
	int nice_value;
	bool is_io;

	// En caso de que consideremos el Real-Time Scheduler. El proceso puede ser de 
	// tipo CFS con una probabilidad type_probability o Real-Time con una probabilidad
	// 1-type_probability.
	aux = dist(generator);
	//std::cout << "Aux type: " << aux << std::endl;
	if (aux > policy_probability * 10) {
		this->policy = SCHED_RR;
	}
	else {
		this->policy = SCHED_NORMAL;
	}
	
	// El proceso puede tener un valor nice por defecto (0) con probabilidad 
	// nice_probability o puede tener un valor distinto con probabilidad 
	// 1-nice_probability.
	aux = dist(generator);
	//std::cout << "Aux nice: " << aux << std::endl;
	if (aux > nice_probability * 10) {
		dist = std::uniform_int_distribution<int>(MIN_NICE,MAX_NICE);
		nice_value = dist(generator);
	}
	else {
		nice_value = 0;
	}
	this->state = 0;
	this->prio = 0;
	this->static_prio = NICE_TO_PRIO(nice_value);
	this-> normal_prio = 0;
	this->rt_priority = 0;
	this->sched_class = nullptr;
	this->se = SchedEntity();
	set_load_weight(this->static_prio, this->policy, &this->se.load);
	this->se.run_node.my_entity = &this->se;
	this->cpus_allowed = 0;
	this->hard_affinity = false;
	this->pid = pid;
	
	dist = std::uniform_int_distribution<int>(1,max_lifetime);
	this->lifetime = dist(generator);
	upper_bound = (int)ceil(lifetime * window_size);
	aux = 0;
	is_io = false;
	while (aux < lifetime) {
		//std::cout << "Low bound " << (aux+1) << std::endl;
		//std::cout << "Upper bound " << upper_bound << std::endl;
		dist = std::uniform_int_distribution<int>(aux+1,upper_bound);
		u_t = dist(generator);
		//std::cout << "u_t " << u_t << std::endl;
		if (is_io) {
			this->requirements.push_back(Resource("I/0",u_t-aux));
			is_io = false;	
		}
		else {
			this->requirements.push_back(Resource("CPU",u_t-aux));
			is_io = true;
		}
		upper_bound += u_t-aux;
		aux = u_t;
		if (upper_bound > lifetime){
			upper_bound = lifetime;
		}
	}
	//std::cout << std::endl;
	//v_runtime = 0;
	
}