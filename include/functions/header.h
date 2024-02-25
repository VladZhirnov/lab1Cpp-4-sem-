
#include <iostream>

struct Node {
private:
	int _data;
	Node* _left;
	Node* _right;
public:
	Node() : _data(0), _left(nullptr), _right(nullptr) {};
	Node(const int& data) : _data(data), _left(nullptr), _right(nullptr) {};
	int get_key() const;
	Node* get_left() const;
	Node* get_right() const;
	Node*& get_left_true();
	Node*& get_right_true();
	int& get_key_true();
};

class Tree {
	Node* _root;
	void copy_tree(Node*& newNode, const Node* root);
	void delete_tree(Node*& root);
	void print_tree(const Node* root);
	bool insert_key(Node*& node, int key);
	bool check_key(Node*& root, int key);
	bool delete_key(Node*& node, int key);
public:
	Tree();
	Tree(const Tree& other);
	~Tree();
	void print();
	Tree& operator=(const Tree& other);
	bool insert(int key);
	bool contains(int key);
	bool erase(int key);
};

int Node::get_key() const{
	return _data;
}

Node* Node::get_left() const {
	return _left;
}

Node* Node::get_right() const {
	return _right;
}

Node*& Node::get_left_true(){
	return _left;
}

Node*& Node::get_right_true(){
	return _right;
}

int& Node::get_key_true() {
	return _data;
}

Tree::Tree() : _root(nullptr) {};

Tree::Tree(const Tree& other) {
	_root = nullptr;
	copy_tree(_root, other._root);
}

void Tree::copy_tree(Node*& newNode, const Node* sourceNode) {
	if (sourceNode == nullptr) {
		newNode = nullptr;
		return;
	}
	newNode = new Node(sourceNode->get_key());
	copy_tree(newNode->get_left_true(), sourceNode->get_left());
	copy_tree(newNode->get_right_true(), sourceNode->get_right());
}

Tree::~Tree() {
	delete_tree(_root);
	_root = nullptr;
}

void Tree::delete_tree(Node*& root) {
	if (root == nullptr) return;
	if (root->get_left() != nullptr || root->get_right() != nullptr) {
		delete_tree(root->get_left_true());
		delete_tree(root->get_right_true());
	}
	delete root;
	root = nullptr;
}

void Tree::print() {
	print_tree(_root);
}

void Tree::print_tree(const Node* root) {
	if (root == nullptr) return;
	std::cout << root->get_key() << " ";
	print_tree(root->get_left());
	print_tree(root->get_right());
	
}

Tree& Tree::operator=(const Tree& other) {
	if (this != &other) { 
		delete_tree(_root);
		copy_tree(_root, other._root);
	}
	return *this;
}

bool Tree::insert(int key) {
	return insert_key(_root, key);
}

bool Tree::insert_key(Node*& node, int key) {
	if (node == nullptr) {
		node = new Node(key);
		return true;
	}
	if (key < node->get_key()) {
		return insert_key(node->get_left_true(), key);
	}
	else if (key > node->get_key()) {
		return insert_key(node->get_right_true(), key);
	}
	return false;
}

bool Tree::contains(int key) {
	return check_key(_root, key);
}

bool Tree::check_key(Node*& node, int key) {
	if (node == nullptr) {
		return false;
	}
	if (node->get_key() == key) {
		return true;
	}
	if (key < node->get_key()) {
		return check_key(node->get_left_true(), key);
	}
	else{
		return check_key(node->get_right_true(), key);
	}
}

bool Tree::erase(int key) {
	return delete_key(_root, key);
}

bool Tree::delete_key(Node*& node, int key) {
	if (node == nullptr) return false;
	if (key < node->get_key()) {
		return delete_key(node->get_left_true(), key);
	}
	else if (key > node->get_key()) {
		return delete_key(node->get_right_true(), key);
	}
	else {
		if (node->get_left() == nullptr && node->get_right() == nullptr) {
			delete node;
			node = nullptr;
			return true;
		}
		else if (node->get_left() == nullptr) {
			Node* temp = node;
			node = node->get_right();
			delete temp;
			return true;
		}
		else if (node->get_right() == nullptr) {
			Node* temp = node;
			node = node->get_left();
			delete temp;
			return true;
		}
		else {
			Node* temp = node->get_right();
			while (temp->get_left() != nullptr) {
				temp = temp->get_left();
			}
			node->get_key_true() = temp->get_key();
			return delete_key(node->get_right_true(), temp->get_key());
		}
	}
}