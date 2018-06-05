#ifndef CPU_H
#define CPU_H

#include "task.h"

class CPU {

	public:
		bool occupied;
		Task *current;

		CPU();

		void consume_time(unsigned int time);
};

#endif