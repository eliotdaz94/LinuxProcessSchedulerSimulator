#ifndef RB_NODE_H
#define RB_NODE_H

#include <string>

class RedBlackNode {
	
	public:
		
		int value;
		std::string color;
		RedBlackNode *left;
		RedBlackNode *right;
		RedBlackNode *parent;
		
		RedBlackNode(int value);

		RedBlackNode(std::string color);
		
		RedBlackNode(int value, std::string color);

};

#endif