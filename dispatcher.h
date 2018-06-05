#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "cpu.h"
#include "cfs_rq.h"

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq);

#endif