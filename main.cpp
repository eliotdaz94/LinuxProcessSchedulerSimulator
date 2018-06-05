#include <thread>
#include "task.h"
#include "task_generator.h"
#include "sched_class.h"
#include "threshold.h"
#include "cfs_rq.h"
#include "fair_sched_class.h"
#include <iostream>

#define PI 3.14159265

int main() {
	int nr_task_gen = 0;
	FairSchedClass fair_class;
	CFSRunQueue cfs_rq;
	Threshold thresh(500, 500, PI/2, 500, 1e-8);
	std::thread move(&Threshold::move_threshold, &thresh);
	std::thread task_gen(task_generator, 1000, 0.8, 0.8, 0.3, &fair_class,
						 &cfs_rq, &thresh, &nr_task_gen);
	Threshold t(0.0,10.0,15.0,2.0,5.0);
	task_gen.join();
	std::cout << "Me canse de generar procesos." << std::endl;
	std::cout << "Genere: " << nr_task_gen << std::endl;
	thresh.exit = true;
	move.join();
	std::cout << "Total nodes: " << cfs_rq.tasks_timeline.nodes << std::endl;
	cfs_rq.tasks_timeline.print_tree();
	cfs_rq.tasks_timeline.in_order();
	return 0;
}
/*
int main(){
	RedBlackTree* my_tree = new RedBlackTree();
	my_tree->insert(new RedBlackNode(278));
	my_tree->insert(new RedBlackNode(190));
	my_tree->insert(new RedBlackNode(18));
	my_tree->insert(new RedBlackNode(321));
	my_tree->insert(new RedBlackNode(331));
	my_tree->insert(new RedBlackNode(96));
	my_tree->insert(new RedBlackNode(439));
	my_tree->insert(new RedBlackNode(378));
	std::cout << "Total nodes: " << my_tree->nodes << std::endl;
	my_tree->print_tree();
	
	return 0;
}
*/