#ifndef CPU_H
#define CPU_H

#include "task.h"

class CPU {

	public:
		unsigned int time;
		bool occupied;
		Task *current;

		CPU();

		void consume_time();
};

#endif