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
	FairSchedClass fair_class;
	CFSRunQueue cfs_rq;
	Threshold thresh(500, 500, PI/2, 500, 1e-8);
	int nr_task_gen = 0;
	bool exit = false;
	std::mutex write;
	//std::thread dispat(dispatcher, cpus, nr_cpus, &cfs_rq);
	std::thread move(&Threshold::move_threshold, &thresh);
	std::thread task_gen(task_generator, 1000, 0.8, 0.8, 0.3, &fair_class,
						 &cfs_rq, &thresh, &nr_task_gen, &write);
	task_gen.join();
	std::cout << "Me canse de generar procesos." << std::endl;
	std::cout << "Genere: " << nr_task_gen << std::endl;
	thresh.exit = true;
	move.join();
	std::cout << "Total nodes: " << cfs_rq.tasks_timeline.nodes << std::endl;
	cfs_rq.tasks_timeline.print_tree();
	cfs_rq.tasks_timeline.in_order();
	std::cout << "Nodo mas izquierdo: " << cfs_rq.tasks_timeline.tree_minimum()->value << std::endl;
	std::thread dispat(dispatcher, cpus, nr_cpus, &cfs_rq, &exit, &write);
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "Ya dormi" << std::endl;
	exit = true;
	dispat.join();
	
	return 0;
}