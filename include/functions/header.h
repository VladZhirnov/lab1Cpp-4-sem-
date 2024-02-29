#include <vector>
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
	double measure_fill_time(size_t num_elements);
	double measure_search_time(size_t num_attempts);
	double measure_insert_and_erase_time(size_t num_attempts);
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
	if (key <= node->get_key()) {
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


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

double Tree::measure_fill_time(size_t num_elements) {
	double total_time = 0.0;
	for (int attempt = 0; attempt < 100; ++attempt) {
		clock_t start_time = clock();
		for (size_t i = 0; i < num_elements; ++i) {
			insert(lcg());
		}
		clock_t end_time = clock();
		total_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
		delete_tree(_root);
		_root = nullptr;
	}
	return total_time / 100.0; 
}

double Tree::measure_search_time(size_t num_elements) {
	for (size_t i = 0; i < num_elements; ++i) {
		insert(lcg());
	}
	double total_time = 0.0;
	for (int attempt = 0; attempt < 1000; ++attempt) {
		int key_to_find = lcg();
		clock_t start_time = clock();
		contains(key_to_find);
		clock_t end_time = clock();
		total_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	}
	return total_time / 1000.0;
}

double Tree::measure_insert_and_erase_time(size_t num_elements) {
	for (size_t i = 0; i < num_elements; ++i) {
		insert(lcg());
	}
	double total_time_add = 0.0;
	double total_time_remove = 0.0;
	for (int attempt = 0; attempt < 1000; ++attempt) {
		int key_to_add = lcg();
		clock_t start_time_add = clock();
		insert(key_to_add);
		clock_t end_time_add = clock();
		total_time_add += static_cast<double>(end_time_add - start_time_add) / CLOCKS_PER_SEC;
		int key_to_remove = lcg();
		clock_t start_time_remove = clock();
		erase(key_to_remove);
		clock_t end_time_remove = clock();
		total_time_remove += static_cast<double>(end_time_remove - start_time_remove) / CLOCKS_PER_SEC;
	}
	double avg_time_add = total_time_add / 1000.0; 
	double avg_time_remove = total_time_remove / 1000.0; 
	return (avg_time_add + avg_time_remove) / 2.0; 
}

double measure_fill_time_vector(size_t num_elements) {
	double total_time = 0.0;
	for (int attempt = 0; attempt < 100; ++attempt) {
		clock_t start_time = clock();
		std::vector<int> vec;
		for (size_t i = 0; i < num_elements; ++i) {
			vec.push_back(lcg());
		}
		clock_t end_time = clock();
		total_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	}
	return total_time / 100.0;
}

double measure_search_time_vector(size_t num_elements) {
	std::vector<int> vec;
	for (size_t i = 0; i < num_elements; ++i) {
		vec.push_back(lcg());
	}
	double total_time = 0.0;
	for (int attempt = 0; attempt < 1000; ++attempt) {
		int key_to_find = lcg();
		clock_t start_time = clock();
		bool found = std::find(vec.begin(), vec.end(), key_to_find) != vec.end();
		clock_t end_time = clock();
		total_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	}
	return total_time / 1000.0;
}

double measure_insert_and_erase_time_vector(size_t num_elements) {
	std::vector<int> vec;
	for (size_t i = 0; i < num_elements; ++i) {
		vec.push_back(lcg());
	}
	double total_time_add = 0.0;
	double total_time_remove = 0.0;
	for (int attempt = 0; attempt < 1000; ++attempt) {
		int key_to_find = lcg();
		clock_t start_time_add = clock();
		vec.push_back(key_to_find);
		clock_t end_time_add = clock();
		total_time_add += static_cast<double>(end_time_add - start_time_add) / CLOCKS_PER_SEC;
		clock_t start_time_remove = clock();
		auto it = std::find(vec.begin(), vec.end(), key_to_find);
		if (it != vec.end()) {
			vec.erase(it);
		}
		clock_t end_time_remove = clock();
		total_time_remove += static_cast<double>(end_time_remove - start_time_remove) / CLOCKS_PER_SEC;
	}
	double avg_time_add = total_time_add / 1000.0;
	double avg_time_remove = total_time_remove / 1000.0;
	return (avg_time_add + avg_time_remove) / 2.0;
}

std::vector<int> create_vector_with_dublicates(std::vector<int> old_vector) {
	Tree tree;
	for (int val : old_vector) {
		tree.insert(val);
	}
	std::vector<int> dublicates;
	for (int val : old_vector) {
		int count = 0;
		while (tree.contains(val)) {
			count++;
			tree.erase(val);
		}
		if (count > 2 || count == 2) {
			dublicates.push_back(val);
		}
	}
	return dublicates;
}