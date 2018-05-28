#ifndef RB_NODE_H
#define RB_NODE_H

#include <string>

class RB_Node {
	
	public:
		
		int value;
		std::string color;
		RB_Node *left;
		RB_Node *right;
		RB_Node *parent;
		
		RB_Node(int value);

		RB_Node(std::string color);
		
		RB_Node(int value, std::string color);

};

#endif