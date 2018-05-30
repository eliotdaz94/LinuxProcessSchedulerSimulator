#include "rb_tree.h"
#include <iostream>
#include <string>
#include <vector>

RedBlackTree::RedBlackTree() {
	this->nil = new RedBlackNode("BLACK");
	//this->nil->left = this->nil;
	//this->nil->right = this->nil;
	this->root = this->nil;
	this->nodes = 0;
}

void RedBlackTree::left_rotate(RedBlackNode *x) {

	RedBlackNode *y;
	y = x->right;
	x->right = y->left;
	if (y->left != this->nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->nil) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;	
	}
	y->left = x;
	x->parent = y;
}

void RedBlackTree::right_rotate(RedBlackNode *x) {

	RedBlackNode *y;
	y = x->left;
	x->left = y->right;
	if (y->right != this->nil) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->nil) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;	
	}
	y->right = x;
	x->parent = y;
}

void RedBlackTree::insert_fixup(RedBlackNode *z) {

	RedBlackNode *y;
	while (z->parent->color == "RED") {
		// Cuando mi padre es el hijo izquierdo de mi abuelo.
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			// Si mi tio es de color RED. Caso 1.
			if (y->color == "RED") {
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			// Si mi tio es de color BLACK.
			else {
				// Si soy el hijo derecho de mi padre. Caso 2.
				if (z == z->parent->right) {
					z = z->parent;
					left_rotate(z);
				}
				// Soy el hijo izquierdo de mi padre. Caso 3
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				right_rotate(z->parent->parent);
			}
		}
		// Cuando mi padre es el hijo derecho de mi abuelo.
		else {
			y = z->parent->parent->left;
			// Si mi tio es de color RED. Caso 1.
			if (y->color == "RED") {
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			// Si mi tio es de color BLACK.
			else {
				// Si soy el hijo izquierdo de mi padre. Caso 2.
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				// Soy el hijo derecho de mi padre. Caso 3
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				left_rotate(z->parent->parent);
			}	
		}
	}
	this->root->color = "BLACK";
}

void RedBlackTree::insert(RedBlackNode *z) {
	RedBlackNode *x;
	RedBlackNode *y;
	y = this->nil;
	x = this->root;
	while (x != this->nil) {
		y = x;
		if (z->value < x->value) {
			x = x->left;
		}
		else {
			x = x->right;	
		}
	}
	z->parent = y;
	if (y == this->nil) {
		this->root = z;
	}
	else if (z->value < y->value) {
		y->left = z;
	}
	else {
		y->right = z;	
	}
	z->left = this->nil;
	z->right = this->nil;
	z->color = "RED";
	insert_fixup(z);
	this->nodes = this->nodes + 1;
}

void RedBlackTree::transplant(RedBlackNode *u, RedBlackNode *v) {

	if (u->parent == this->nil) {
		this->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RedBlackTree::remove(RedBlackNode *z) {
	
	RedBlackNode *x;
	RedBlackNode *y;
	std::string y_original_color;

	y = z;
	y_original_color = y->color;
	if (z->left == this->nil) {
		x = z->right;
		RedBlackTree::transplant(z, z->right);
	}
	else if (z->right == this->nil) {
		x = z->left;
		RedBlackTree::transplant(z, z->left);
	}
	else {
		y = RedBlackTree::tree_minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			RedBlackTree::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RedBlackTree::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == "BLACK") {
		RedBlackTree::remove_fixup(x);
	}
	this->nodes = this->nodes - 1;
}

void RedBlackTree::remove_fixup(RedBlackNode *x) {

	RedBlackNode *w;

	while (x != this->root && x->color == "BLACK") {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == "RED") {
				w->color = "BLACK";
				x->parent->color = "RED";
				RedBlackTree::left_rotate(x->parent);
				w = x->parent->right; 
			}
			if (w->left->color == "BLACK" && w->right->color == "BLACK") {
				w->color = "RED";
				x = x->parent;
			}
			else if (w->right->color == "BLACK") {
				w->left->color == "BLACK";
				w->color == "BLACK";
				RedBlackTree::right_rotate(w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = "BLACK";
			w->right->color = "BLACK";
			RedBlackTree::left_rotate(x->parent);
			x = this->root;
		}
		else {
			w = x->parent->left;
			if (w->color == "RED") {
				w->color = "BLACK";
				x->parent->color = "RED";
				RedBlackTree::left_rotate(x->parent);
				w = x->parent->left; 
			}
			if (w->right->color == "BLACK" && w->left->color == "BLACK") {
				w->color = "RED";
				x = x->parent;
			}
			else if (w->left->color == "BLACK") {
				w->right->color == "BLACK";
				w->color == "BLACK";
				RedBlackTree::right_rotate(w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = "BLACK";
			w->left->color = "BLACK";
			RedBlackTree::left_rotate(x->parent);
			x = this->root;
		}
	}
	x->color = "BLACK";
}

RedBlackNode* RedBlackTree::tree_minimum(RedBlackNode *x) {

	RedBlackNode *y = x;

	while (y->left != this->nil) {
		y = y->left;
	}
	return y;
}

void RedBlackTree::print_tree() {
	std::vector<RedBlackNode*> children;
	RedBlackNode *aux_node;
	int power = 1;
	int aux_power = 0;
	bool complete = false;
	children.push_back(this->root);
	while (!children.empty() && !complete) {
		aux_node = children.front();
		std::cout << aux_node->value << " ";
		if (aux_node->left !=  nullptr && aux_node->right != nullptr) {		
			children.push_back(aux_node->left);
			children.push_back(aux_node->right);
		}
		children.erase(children.begin());
		aux_power += 1;
		if (aux_power == power) {
			std::cout << std::endl;
			power *= 2;
			aux_power = 0;
			if (children.size() != power) {
				complete = true;
			}
		}
	}
}