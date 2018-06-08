#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <mutex>
#include "cpu.h"
#include "cfs_rq.h"

void dispatcher(CPU cpus[], int nr_cpus, int *nr_task_gen, IODev *io_device,
				CFSRunQueue *cfs_rq, std::mutex *write, bool *exit);

#endif