#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"

class RB_Tree {
	
	public:
		
		RB_Node *root;
		RB_Node *nil;
		int nodes;

		RB_Tree();
		
		void left_rotate(RB_Node *x);

		void right_rotate(RB_Node *x);

		void insert_fixup(RB_Node *z);

		void insert(RB_Node *z);

		void transplant(RB_Node *u, RB_Node *v);

		void remove(RB_Node *z);

		void remove_fixup(RB_Node *x);

		RB_Node* tree_minimum(RB_Node *x);

		void print_tree();

};

#endif