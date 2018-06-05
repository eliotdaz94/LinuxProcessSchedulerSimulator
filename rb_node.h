#ifndef RB_NODE_H
#define RB_NODE_H

#include <string>

class SchedEntity;

class RedBlackNode {
	
	public:
		
		int value;
		std::string color;
		RedBlackNode *left;
		RedBlackNode *right;
		RedBlackNode *parent;
		SchedEntity *my_entity;

		RedBlackNode();

		RedBlackNode(int value);

		RedBlackNode(std::string color);
		
		RedBlackNode(int value, std::string color);

};

#endif