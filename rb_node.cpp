#include "rb_node.h"

RedBlackNode::RedBlackNode(){
	this->value = -1;
	this->color = "BLACK";
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}


RedBlackNode::RedBlackNode(int value) {
	this->value = value;
	this->color = "BLACK";
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

RedBlackNode::RedBlackNode(std::string color) {
	this->value = -1;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

RedBlackNode::RedBlackNode(int value, std::string color) {
	this->value = value;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}