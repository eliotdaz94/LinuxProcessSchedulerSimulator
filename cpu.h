#ifndef CPU_H
#define CPU_H

#include <mutex>
#include "task.h"

class CPU {

	public:
		unsigned int time;
		//bool occupied;
		Task *current;
		std::mutex occupied;

		CPU();

		void consume_time(int cpu, std::mutex *write);
};

#endif