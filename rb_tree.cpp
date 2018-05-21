#include <string>

using namespace std;

class RB_Node {
	public:
		int key;
		int value;
		string color;
		RB_Node *p;
		RB_Node *left;
		RB_Node *right;

		RB_Node(string c) {
			color = c;
			p = nullptr;
			left = nullptr;
			right = nullptr;
		}

		RB_Node(int k, int v) {
			key = k;
			value = v;
			p = nullptr;
			left = nullptr;
			right = nullptr;	
		}
};

class RB_Tree {
	public:
		RB_Node *root;
		RB_Node *nil;

		RB_Tree() {
			nil = new RB_Node("BLACK");
			root = nil;
		}
};

void left_rotate(RB_Tree T, RB_Node *x) {
	RB_Node *y;
	y = x->right;
	x->right = y->left;
	if (y->left == T.nil) {
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p != T.nil) {
		T.root = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else {
		x->p->right = y;	
	}
	y->left = x;
	x->p = y;
}

void right_rotate(RB_Tree T, RB_Node *x) {
	RB_Node *y;
	y = x->left;
	x->left = y->right;
	if (y->right != T.nil) {
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == T.nil) {
		T.root = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else {
		x->p->right = y;	
	}
	y->right = x;
	x->p = y;
}

void insert_fixup(RB_Tree T, RB_Node *z) {
	RB_Node *y;
	while (z->p->color == "RED") {
		// Cuando mi padre es el hijo izquierdo de mi abuelo.
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			// Si mi tio es de color RED. Caso 1.
			if (y->color == "RED") {
				z->p->color = "BLACK";
				y->color = "BLACK";
				z->p->p->color = "RED";
				z = z->p->p;
			}
			// Si mi tio es de color BLACK.
			else {
				// Si soy el hijo derecho de mi padre. Caso 2.
				if (z == z->p->right) {
					z = z->p;
					left_rotate(T,z);
				}
				// Soy el hijo izquierdo de mi padre. Caso 3
				z->p->color = "BLACK";
				z->p->p->color = "RED";
				right_rotate(T,z->p->p);
			}
		}
		// Cuando mi padre es el hijo derecho de mi abuelo.
		else {
			y = z->p->p->left;
			// Si mi tio es de color RED. Caso 1.
			if (y->color == "RED") {
				z->p->color = "BLACK";
				y->color = "BLACK";
				z->p->p->color = "RED";
				z = z->p->p;
			}
			// Si mi tio es de color BLACK.
			else {
				// Si soy el hijo izquierdo de mi padre. Caso 2.
				if (z == z->p->left) {
					z = z->p;
					right_rotate(T,z);
				}
				// Soy el hijo derecho de mi padre. Caso 3
				z->p->color = "BLACK";
				z->p->p->color = "RED";
				left_rotate(T,z->p->p);
			}	
		}
	}
	T.root->color = "BLACK";
}

void insert(RB_Tree T, RB_Node *z) {
	RB_Node *x;
	RB_Node *y;
	y = T.nil;
	x = T.root;
	while (x != T.nil) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;	
		}
	}
	z->p = y;
	if (y == T.nil) {
		T.root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;	
	}
	z->left = T.nil;
	z->right = T.nil;
	z->color = "RED";
	insert_fixup(T,z);
}

int main(){
	RB_Tree my_tree;
	insert(my_tree, new RB_Node(1,11));
	insert(my_tree, new RB_Node(2,12));
	insert(my_tree, new RB_Node(3,13));
	insert(my_tree, new RB_Node(4,14));
	insert(my_tree, new RB_Node(5,15));
	return 0;
}