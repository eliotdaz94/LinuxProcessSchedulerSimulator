#include "rb_tree.h"
#include <iostream>
#include <string>
#include <vector>

RB_Tree::RB_Tree() {
	this->nil = new RB_Node("BLACK");
	//this->nil->left = this->nil;
	//this->nil->right = this->nil;
	this->root = this->nil;
	this->nodes = 0;
}

void RB_Tree::left_rotate(RB_Node *x) {

	RB_Node *y;
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

void RB_Tree::right_rotate(RB_Node *x) {

	RB_Node *y;
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

void RB_Tree::insert_fixup(RB_Node *z) {

	RB_Node *y;
	while (z->parent->color == "RED") {
<<<<<<< HEAD
=======
		//std::cout << "debug" << std::endl;
>>>>>>> a35b69896832bcd7f19234b448bcb5bcaf7a6674
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

void RB_Tree::insert(RB_Node *z) {
	RB_Node *x;
	RB_Node *y;
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
}

void RB_Tree::transplant(RB_Node *u, RB_Node *v) {

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

void RB_Tree::remove(RB_Node *z) {
	
	RB_Node *x;
	RB_Node *y;
	std::string y_original_color;

	y = z;
	y_original_color = y->color;
	if (z->left == this->nil) {
		x = z->right;
		RB_Tree::transplant(z, z->right);
	}
	else if (z->right == this->nil) {
		x = z->left;
		RB_Tree::transplant(z, z->left);
	}
	else {
		RB_Tree::tree_minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			RB_Tree::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RB_Tree::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == "BLACK") {
		RB_Tree::remove_fixup(x);
	}
	this->nodes = this->nodes - 1;
}

void RB_Tree::remove_fixup(RB_Node *x) {

	RB_Node *w;

	while (x != this->root && x->color == "BLACK") {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == "RED") {
				w->color = "BLACK";
				x->parent->color = "RED";
				RB_Tree::left_rotate(x->parent);
				w = x->parent->right; 
			}
			if (w->left->color == "BLACK" && w->right->color == "BLACK") {
				w->color = "RED";
				x = x->parent;
			}
			else if (w->right->color == "BLACK") {
				w->left->color == "BLACK";
				w->color == "BLACK";
				RB_Tree::right_rotate(w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = "BLACK";
			w->right->color = "BLACK";
			RB_Tree::left_rotate(x->parent);
			x = this->root;
		}
		else {
			w = x->parent->left;
			if (w->color == "RED") {
				w->color = "BLACK";
				x->parent->color = "RED";
				RB_Tree::left_rotate(x->parent);
				w = x->parent->left; 
			}
			if (w->right->color == "BLACK" && w->left->color == "BLACK") {
				w->color = "RED";
				x = x->parent;
			}
			else if (w->left->color == "BLACK") {
				w->right->color == "BLACK";
				w->color == "BLACK";
				RB_Tree::right_rotate(w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = "BLACK";
			w->left->color = "BLACK";
			RB_Tree::left_rotate(x->parent);
			x = this->root;
		}
	}
	x->color = "BLACK";
}

RB_Node* RB_Tree::tree_minimum(RB_Node *x) {

	RB_Node *y = x;

	while (y->left != this->nil) {
		y = y->left;
	}
	return y;
}

void RB_Tree::print_tree() {
	std::vector<RB_Node*> children;
	RB_Node *aux_node;
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