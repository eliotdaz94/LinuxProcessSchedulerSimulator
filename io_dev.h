#ifndef IO_DEV_H
#define IO_DEV_H

#include <vector>
#include <mutex>
#include "task.h"

class IODev {

	public:
		std::vector<Task*> wait_queue;
		unsigned int time;
		bool occupied;
		Task *current;
		std::mutex use;

		IODev();

		void consume_time(std::mutex *write);
};

#endif