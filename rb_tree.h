#ifndef RB_TREE_H
#define RB_TREE_H

#include <mutex>
#include "rb_node.h"

class RedBlackTree {
	
	public:

		RedBlackNode *root;
		RedBlackNode *nil;
		int nodes;
		std::mutex creator;  
		std::mutex dispatcher;

		RedBlackTree();
		
		void left_rotate(RedBlackNode *x);

		void right_rotate(RedBlackNode *x);

		void insert_fixup(RedBlackNode *z);

		void insert(RedBlackNode *z);

		void transplant(RedBlackNode *u, RedBlackNode *v);

		void remove(RedBlackNode *z);

		void remove_fixup(RedBlackNode *x);

		RedBlackNode* tree_minimum(RedBlackNode *x);

		void print_tree();

};

#endif