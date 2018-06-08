#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include "task.h"
#include "task_generator.h"
#include "sched_class.h"
#include "threshold.h"
#include "cfs_rq.h"
#include "fair_sched_class.h"
#include "cpu.h"
#include "io_dev.h"
#include "dispatcher.h"

#define PI 3.14159265

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " nr_cpus " << std::endl;
		std::cout << "  nr_cpus Number of CPU's to be used in the simulation." 
				  << std::endl;
		return 0;
	}
	int nr_cpus = std::stoi(argv[1]);
	CPU *cpus = new CPU[nr_cpus];
	IODev io_dev;
	FairSchedClass fair_class;
	CFSRunQueue cfs_rq;
	Threshold thresh(500, 500, PI/2, 500, 1e-8);
	int nr_task_gen = 0;
	bool exit = false;
	std::mutex write;
	// Iniciamos el movimiento del threshold en un nuevo hilo.
	std::thread move(&Threshold::move_threshold, &thresh);
	// Iniciamos el generador de task en un nuevo hilo.
	std::thread task_gen(task_generator, 1000, 0.8, 0.8, 0.3, &fair_class,
						 &cfs_rq, &thresh, &nr_task_gen, &write);
	task_gen.join();
	write.lock();
	std::cout << "###  Se detiene generacion de tasks  ###" << std::endl;
	std::cout << "### Se generaron un total de " << nr_task_gen << " tasks ###"
			  << std::endl;
	write.unlock();
	thresh.exit = true;
	move.join();
	// Iniciamos el despachador de task en un nuevo hilo.
	std::thread dispat(dispatcher, cpus, nr_cpus, &io_dev, &cfs_rq, &write, &exit);
	exit = true;
	dispat.join();
	
	return 0;
}