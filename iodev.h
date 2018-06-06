#ifndef IODEV_H
#define IODEV_H

#include <mutex>
#include "task.h"

class IODEV {

	public:
		unsigned int time;
		bool occupied;
		Task *current;

		IODEV();

		void consume_time(std::mutex *write);
};

#endif