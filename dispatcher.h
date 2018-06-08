#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <mutex>
#include "cpu.h"
#include "cfs_rq.h"

void dispatcher(CPU cpus[], int nr_cpus, IODev *io_dev, CFSRunQueue *cfs_rq, 
				std::mutex *write, bool *exit);

#endif