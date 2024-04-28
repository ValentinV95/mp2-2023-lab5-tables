#pragma once
#include "stack.h"
#include <algorithm>

template <class K, class T>
class OrderedTable {
	struct Node {
		K key;
		T data;
		Node* l, * r;
		int h;
		Node(K key_, T data_, Node* l_ = nullptr, Node* r_ = nullptr, int h_ = 1): key(key_),data(data_),l(l_),r(r_),h(h_) {};
		int diff() {
			if (l && r) return (l->h - r->h);
			if (l == nullptr && r) return -r->h;
			if (l && r == nullptr) return l->h;
			return 0;
		}
		void counth() {
			if (l && r) h = std::max(l->h, r->h)+1;
			else if (l == nullptr && r) h= r->h+1;
			else  if (l && r == nullptr) h = l->h + 1;
			else h = 1;
		}
	};
	Node* head;
	void srt(Node* nd, Node* top) noexcept {
		if (top) {
			if (top->l == nd) {
				std::swap(top->l, nd->l->r);
				std::swap(top->l, nd->l);
				nd->counth();
				top->l->counth();
			}
			else {
				std::swap(top->r, nd->l->r);
				std::swap(top->r, nd->l);
				nd->counth();
				top->r->counth();
			}
		}
		else {
			std::swap(head, nd->l->r);
			std::swap(head, nd->l);
			nd->counth();
			head->counth();
		}
	}
	void slt(Node* nd, Node* top) noexcept {
		if (top) {
			if (top->l == nd) {
				std::swap(top->l, nd->r->l);
				std::swap(top->l, nd->r);
				nd->counth();
				top->l->counth();
			}
			else {
				std::swap(top->r, nd->r->l);
				std::swap(top->r, nd->r);
				nd->counth();
				top->r->counth();
			}
		}
		else {
			std::swap(head, nd->r->l);
			std::swap(head, nd->r);
			nd->counth();
			head->counth();
		}
	}
	void brt(Node* nd, Node* top) noexcept {
		slt(nd->l, nd);
		srt(nd, top);
	}
	void blt(Node* nd, Node* top) noexcept {
		srt(nd->r, nd);
		slt(nd, top);
	}
public:
	OrderedTable() {
		head = nullptr;
	}
	~OrderedTable() {
		TStack<Node*> S;
		Node* nd = head;
		S.push_back(nd);
		while (!S.isEmpty()) {
			nd = S.pop_back();
			if (nd) {
				S.push_back(nd->r);
				S.push_back(nd->l);
				delete nd;
			}
		}
		head = nullptr;
	}
	void add(K key_, T data_) {
		if (head) {
			TStack<Node*> S;
			S.push_back(nullptr);
			S.push_back(head);
			while (S.top()) {
				if (key_ > S.top()->key) S.push_back(S.top()->r);
				else if (key_ < S.top()->key) S.push_back(S.top()->l);
				else throw std::invalid_argument("In this table already exist element with this key");
			}
			S.pop_back();
			if (key_ > S.top()->key) S.top()->r = new Node{ key_,data_ };
			else S.top()->l = new Node { key_, data_ };
			Node* nd = S.pop_back();
			size_t oldh;
			while (nd) {
				oldh = nd->h;
				nd->counth();
				if (nd->diff() == -2) {
					if (nd->r->diff() == -1) slt(nd, S.top());
					else blt(nd, S.top());
					break;
				}
				else if (nd->diff() == 2) {
					if (nd->l->diff() == 1) srt(nd, S.top());
					else brt(nd, S.top());
					break;
				}
				else if (nd->h == oldh) break;
				nd = S.pop_back();
			}
		}
		else head = new Node{ key_,data_ };
	}
	T find(const K& key_) const {
		Node* nd = head;
		while (nd && nd->key != key_) {
			if (key_ > nd->key) nd = nd->r;
			else nd = nd->l;
		}
		if (nd) return nd->data;
		throw std::invalid_argument("There are no such key in this table");
	}
	void del(const K& key_) {
		TStack<Node*> S;
		S.push_back(nullptr);
		S.push_back(head);
		while (S.top() && S.top()->key != key_) {
			if (key_ > S.top()->key) S.push_back(S.top()->r);
			else S.push_back(S.top()->l);
		}
		if (S.top()) {
			Node* nd = S.top();
			if (nd->r) {
				S.push_back(nd->r);
				while (S.top()->l)
					S.push_back(S.top());
				nd->data = S.top()->data;
				nd->key = S.top()->key;
				nd = S.top();
				S.pop_back();
				if (S.top()->l == nd) S.top()->l = nd->r;
				else S.top()->r = nd->r;
				delete nd;
			}
			else {
				if (nd == head) {
					head = head->l;
					delete nd;
					return;
				}
				S.pop_back();
				if (S.top()->l == nd) S.top()->l = nd->l;
				else S.top()->r = nd->l;
				delete nd;
			};
			nd = S.pop_back();
			bool fl = true;
			size_t oldh;
			while (nd && fl) {
				oldh = nd->h;
				nd->counth();
				if (nd->diff() == -2) {
					fl = nd->r->diff();
					if (nd->r->diff() == 0 || nd->r->diff() == -1) slt(nd, S.top());
					else blt(nd, S.top());
				}
				else if (nd->diff() == 2) {
					fl = nd->l->diff();
					if (nd->l->diff() == 0 || nd->l->diff() == 1) srt(nd, S.top());
					else brt(nd, S.top());
				}
				else if (nd->h == oldh) break;
				nd = S.pop_back();
			}
		}
	}
};