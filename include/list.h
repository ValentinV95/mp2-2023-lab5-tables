#pragma once
//using namespace std;
//#include <iostream>
#include <stdexcept>

template <class T>
class list {
	struct node {
		T val;
		node* pnext;
		node(const T& value) : val(value), pnext(nullptr) {}

	};
	node* head;
	int sz;
public:
	list() {
		head = nullptr;
		sz = 0;
	}
	list(const list& l) {
		if (l.head == nullptr) {
			head = nullptr;
			return;
		}
		sz = l.sz;
		head = new node(l.head->val);
		node* current = head;
		node* lcurrent = l.head->pnext;
		while (lcurrent != nullptr) {
			current->pnext = new node(lcurrent->val);
			lcurrent = lcurrent->pnext;
			current = current->pnext;
		}
	}
	~list() {
		node* current = head;
		while (current != nullptr) {
			node* nextdel = current->pnext;
			delete current;
			current = nextdel;
		}
		sz = 0;
	}
	void push_front(const T& value) {
		node* newf = new node(value);
		newf->pnext = head;
		head = newf;
		sz++;
	}

	void pop_front() {
		if (head == nullptr) {
			throw std::logic_error("No such element");
		}
		node* ptmp = head->pnext;
		delete head;
		head = ptmp;
		sz--;
	}
	void insert(int pos, const T& value) { 
		if (pos < 0 || pos > sz) {
			throw std::out_of_range("Index out of bounds");
		}
		if (pos == 0) {
			push_front(value);
			return;
		}
		node* pafter = head;
		while (pos > 1) {
			pafter = pafter->pnext;
			pos--;
		}
		node* ins = new node(value);
		ins->pnext = pafter->pnext;
		pafter->pnext = ins;
		sz++;
	}
	void push_back(const T& value) {

		if (head == nullptr) {
			push_front(value);
			return;
		}

		node* pcur = head;
		while (pcur->pnext != nullptr) {
			pcur = pcur->pnext;
		}
		node* ins = new node(value);
		pcur->pnext = ins;
		sz++;
	}
	void pop_back() {
		if (head == nullptr) {
			throw std::logic_error("No such element");
		}

		if (head->pnext == nullptr) {
			node* del = head;
			head = nullptr;
			sz--;
			delete del;
			return;
		}
		node* pcur = head;
		while (pcur->pnext->pnext != nullptr) {
			pcur = pcur->pnext;
		}
		node* del = pcur->pnext;
		pcur->pnext = nullptr;
		delete del;
		sz--;
	}
	void erase(int pos) {
		if (pos < 0 || pos > sz) {
			throw std::out_of_range("Index out of bounds");
		}
		if (pos == 0) {
			pop_front();
			return;
		}
		if (pos == sz) {
			pop_back();
			return;
		}
		node* pdelbefore = head;
		for (int i = 0; i < pos - 1; i++) {
			pdelbefore = pdelbefore->pnext;
		}
		node* pdel = pdelbefore->pnext;
		pdelbefore->pnext = pdelbefore->pnext->pnext;
		delete pdel;
		sz--;
	}

	int size() const {
		return sz;
	}
	T& operator[](int pos) const {
		if (pos < 0 || pos > sz) {
			throw std::out_of_range("Index out of bounds");
		}
		node* p = head;
		while (pos > 0) {
			p = p->pnext;
			pos--;
		}
		return p->val;
	}
};