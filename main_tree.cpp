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
	RedBlackTree* my_tree = new RedBlackTree();
	my_tree->insert(new RedBlackNode(1));
	my_tree->insert(new RedBlackNode(2));
	my_tree->insert(new RedBlackNode(3));
	my_tree->insert(new RedBlackNode(4));
	my_tree->insert(new RedBlackNode(5));

	RedBlackNode* node = new RedBlackNode(6);
	my_tree->insert(node);

	my_tree->insert(new RedBlackNode(7));
	my_tree->insert(new RedBlackNode(8));
	my_tree->insert(new RedBlackNode(9));
	my_tree->print_tree();
	std::cout << "Total nodes: " << my_tree->nodes << std::endl;

	my_tree->remove(node);
	my_tree->print_tree();
	std::cout << "Total nodes: " << my_tree->nodes << std::endl;
	

	return(0);
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

/*
int main(){
	RedBlackTree* my_tree = new RedBlackTree();
	my_tree->insert(new RedBlackNode(11));
	my_tree->insert(new RedBlackNode(2));
	my_tree->insert(new RedBlackNode(14));
	my_tree->insert(new RedBlackNode(1));
	my_tree->insert(new RedBlackNode(7));
	my_tree->insert(new RedBlackNode(5));
	my_tree->insert(new RedBlackNode(8));
	my_tree->insert(new RedBlackNode(15));
	std::cout << "Total nodes: " << my_tree->nodes << std::endl;
	my_tree->print_tree();
	my_tree->insert(new RedBlackNode(4));
	std::cout << "Total nodes: " << my_tree->nodes << std::endl;
	my_tree->print_tree();
	return 0;
}
*