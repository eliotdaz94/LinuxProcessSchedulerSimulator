#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unistd.h>
#include "threshold.h"
#include "rb_tree.h"

using namespace std;


/*
int main() {

	double lifetime;
	double boundary;
	bool is_created;

	Threshold threshold(5, 5, 0, 5, 1e-9);
	thread move(&Threshold::move_threshold, &threshold);

	default_random_engine generator;
	uniform_real_distribution<double> distribution(0, 10);

	while (true) {
		lifetime = distribution(generator);
		is_created = threshold.under_threshold(lifetime);
		boundary = threshold.get_boundary();
		cout << "Threshold: " << boundary << "\t| Lifetime: " << lifetime << "\t| Created?: " << is_created << endl;
		usleep(0.20 * 1000000);
	}

	return 0;
}
*/
int main(){
	RB_Tree* my_tree = new RB_Tree();
	my_tree->insert(new RB_Node(1));
	my_tree->insert(new RB_Node(2));
	my_tree->insert(new RB_Node(3));
	my_tree->insert(new RB_Node(4));

	RB_Node* node = new RB_Node(5);
	my_tree->insert(node);
	cout << "main: " << my_tree->nodes << endl;
	
	my_tree->remove(node);
	cout << "main: " << my_tree->nodes << endl;

	return(0);
}