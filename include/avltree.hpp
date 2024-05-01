#pragma once
#include <stdexcept>
#include "stack.hpp"
#include "informer.hpp"

template <typename K, typename T>
class AVLTree {
public:
	AVLTree(Informer& inf = Informer(Table::kOrd)) : head_(nullptr), inf_(inf) {}
	T* find(const K& key);
	void insert(const K& key, const T& value);
	void remove(const K& key);
private:
	class Node {
	public:
		Node(const K& key, const T& value, Node* left, Node* right, size_t height = 1): key_(key), value_(value), left_(left), right_(right), height_(height) {}
		int diff() {
			if (left_ == nullptr && right_ != nullptr) { return -static_cast<int>(right_->height_); }
			else if (left_ != nullptr && right_ == nullptr) { return left_->height_; }
			else if (left_ == nullptr && right_ == nullptr) { return 0; }
			else { return static_cast<int>(left_->height_) - static_cast<int>(right_->height_); }
		}
		K key_;
		T value_;
		Node* left_;
		Node* right_;
		size_t height_;
	};
	void find_rem_right_child(Node* cur, TStack<Node*>& stack) {
		if (cur->right_ == nullptr) {
			cur->key_ = cur->left_->key_;
			cur->value_ = cur->left_->value_;
			delete cur->left_;
			cur->left_ = nullptr;
			inf_.op(5);
			return;
		}
		Node* cur2 = cur->right_;
		inf_.op();
		if (cur2->left_ == nullptr) {
			cur->key_ = cur2->key_;
			cur->value_ = cur2->value_;
			stack.top()->right_ = nullptr;
			delete cur2;
			inf_.op(5);
			return;
		}
		while (cur2->left_ != nullptr) {
			inf_.op(2);
			stack.push(cur2);
			cur2 = cur2->left_;
		}
		cur->key_ = cur2->key_;
		cur->value_ = cur2->value_;
		stack.top()->left_ = nullptr;
		delete cur2;
		inf_.op(4);
	}
	void rotateLeft(Node* a) {
		inf_.op(3);
		Node* b = a->right_;
		a->right_ = b->left_;
		b->left_ = a;
		normalize_height(a);
		normalize_height(b);
	}
	void bigRotateLeft(Node* a) {
		inf_.op(2);
		Node* tmp = a->right_->left_;
		rotateRight(a->right_);
		a->right_ = tmp;
		rotateLeft(a);
	}
	void rotateRight(Node* a) {
		inf_.op(3);
		Node* b = a->left_;
		a->left_ = b->right_;
		b->right_ = a;
		normalize_height(a);
		normalize_height(b);
	}
	void bigRotateRight(Node* a) {
		inf_.op(2);
		Node* tmp = a->left_->right_;
		rotateLeft(a->left_);
		a->left_ = tmp;
		rotateRight(a);
	}
	void normalize_height(Node* a) {
		if (a->left_ == nullptr && a->right_ == nullptr) {
			inf_.op(2);
			a->height_ = 1;
		}
		else {
			inf_.op(3);
			if (a->diff() > 0) { a->height_ = a->left_->height_ + 1; }
			else { a->height_ = a->right_->height_ + 1; }
		}
	}
	void upwards(Node* start, TStack<Node*>& stack) {
		inf_.op(2);
		Node* tmp2 = start;
		Node* tmp3 = start;
		while (!stack.isEmpty()) {
			start = stack.pop();
			if (start->left_ == tmp3) { start->left_ = tmp2; }
			else { start->right_ = tmp2; }
			tmp3 = start;
			inf_.op(3);
			normalize_height(start);
			inf_.op(1);
			if (start->diff() == -2) {
				if (start->right_->diff() == 1) {
					tmp2 = start->right_->left_;
					bigRotateLeft(start);
				}
				else {
					tmp2 = start->right_;
					rotateLeft(start);
				}
				inf_.op(2);
			}
			else if (start->diff() == 2) {
				if (start->left_->diff() == -1) {
					tmp2 = start->left_->right_;
					bigRotateRight(start);
				}
				else {
					tmp2 = start->left_;
					rotateRight(start);
				}
				inf_.op(2);
			}
			else {
				tmp2 = start;
			}
		}
		inf_.op(2);
		if (start == head_) {
			head_ = tmp2;
		}
	}
	Node* head_;
	Informer& inf_;
};

template <typename K, typename T>
T* AVLTree<K, T>::find(const K& key) {
	inf_.op();
	Node* tmp = head_;
	while (tmp != nullptr) {
		inf_.op(3);
		if (key < tmp->key_) {
			tmp = tmp->left_;
		}
		else if (key > tmp->key_) {
			tmp = tmp->right_;
		}
		else {
			return &tmp->value_;
		}
	}
	throw std::runtime_error("Key not found in a tree");
}

template <typename K, typename T>
void AVLTree<K, T>::insert(const K& key, const T& value) {
	inf_.op(3);
	Node* tmp = head_;
	Node* constructed = new Node(key, value, nullptr, nullptr);
	if (tmp == nullptr) {
		head_ = constructed;
		inf_.op();
		return;
	}
	TStack<Node*> stack;
	while (tmp != nullptr) {
		inf_.op(4);
		stack.push(tmp);
		if (key < tmp->key_) {
			tmp = tmp->left_;
		}
		else if (key > tmp->key_) {
			tmp = tmp->right_;
		}
		else {
			throw std::invalid_argument("Key is already in a tree");
		}
	}
	inf_.op(3);
	tmp = stack.pop();
	if (key < tmp->key_) { tmp->left_ = constructed; }
	else { tmp->right_ = constructed; }
	inf_.op(2);
	if (tmp->diff() != 0) { tmp->height_++; }
	upwards(tmp, stack);
}

template <typename K, typename T>
void AVLTree<K, T>::remove(const K& key) {
	Node* tmp = head_;
	Node* tmp2;
	TStack<Node*> stack;
	bool good = false;
	inf_.op(1);
	while (tmp != nullptr) {
		inf_.op(4);
		stack.push(tmp);
		if (key < tmp->key_) {
			tmp = tmp->left_;
		}
		else if (key > tmp->key_) {
			tmp = tmp->right_;
		}
		else {
			good = true;
			break;
		}
	}
	inf_.op(3);
	if (good == false) { throw std::invalid_argument("Key not found in a tree"); }
	tmp = stack.pop();
	if (tmp == head_) {
		if (tmp->left_ != nullptr || tmp->right_ != nullptr) {
			stack.push(tmp);
			inf_.op(2);
			find_rem_right_child(tmp, stack);
		}
		else {
			inf_.op(3);
			delete head_;
			head_ = nullptr;
			return;
		}
	}
	else {
		tmp2 = stack.top();
		inf_.op(2);
		if (tmp->left_ != nullptr || tmp->right_ != nullptr) {
			stack.push(tmp);
			inf_.op(1);
			find_rem_right_child(tmp, stack);
		}
		else {
			if (tmp2->left_ == tmp) { tmp2->left_ = nullptr; }
			else { tmp2->right_ = nullptr; }
			delete tmp;
			tmp = tmp2;
			inf_.op(4);
		}
	}
	inf_.op();
	tmp = stack.top()->left_;
	upwards(tmp, stack);
}
