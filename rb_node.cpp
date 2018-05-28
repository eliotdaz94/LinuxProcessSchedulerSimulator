#include "rb_node.h"

RB_Node::RB_Node(int value) {
	this->value = value;
	this->color = "BLACK";
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

RB_Node::RB_Node(std::string color) {
	this->value = -1;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

RB_Node::RB_Node(int value, std::string color) {
	this->value = value;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}