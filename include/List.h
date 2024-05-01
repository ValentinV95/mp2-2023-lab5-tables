#pragma once
#include <stdexcept>

template <class T>
class List {
protected:
	class Node {
	public:
		T data;
		Node* next;
		Node(T data_ = {}, Node* next_ = nullptr) {
			data = data_;
			next = next_;
		}
	};
	Node* head;
	void add(Node* this_, T val = {}) { //add Node after the one we are pointing to
		this_->next = new Node(val, this_->next);
	}
	void del(Node* this_) { //delete Node after the one we are pointing to
		if (this_->next) {
			Node* tmp = this_->next;
			this_->next = this_->next->next;
			delete tmp;
		}
		else throw std::out_of_range("There are fewer elements in this List");
	}
	Node* get(int ind) const { //get pointer to a Node with this index in this List
		Node* tmp = head;
		for (int i = 0; i < ind; i++) {
			if (tmp == nullptr) throw std::out_of_range("There are fewer elements in this List");
			tmp = tmp->next;
		}
		if (tmp) return tmp;
		else throw std::out_of_range("There are fewer elements in this List");
	}
public:
	List() {
		head = nullptr;
	}
	~List() {
		Node* tmp;
		while (head) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	List(const List& L) {
		Node* tmp1 = L.head;
		if (tmp1) {
			head = new Node(tmp1->data);
			Node* tmp2 = head;
			while (tmp1->next) {
				tmp1 = tmp1->next;
				tmp2->next = new Node(tmp1->data);
				tmp2 = tmp2->next;
			}
		}
		else head = nullptr;
	}
	bool operator==(const List& L) const noexcept {
		Node* tmp1 = head, * tmp2 = L.head;
		while (tmp1 && tmp2) {
			if (tmp1->data != tmp2->data) return false;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		if (tmp1 || tmp2) return false;
		return true;
	}
	bool operator!=(const List& L) const noexcept {
		return !(*this == L);
	}
	List& operator=(const List& L) {
		if (this != &L) {
			Node* tmp = L.head;
			this->~List();
			if (tmp) {
				head = new Node(tmp->data);
				Node* tmp2 = head;
				while (tmp->next) {
					tmp = tmp->next;
					tmp2->next = new Node(tmp->data);
					tmp2 = tmp2->next;
				};
			};
		};
		return *this;
	}
	void add_head(T val = {}) {
		head = new Node(val, head);
	}
	void add(int ind, T val = {}) { // add an element to the specified position
		if (ind == 0) add_head(val);
		else add(get(ind-1), val);
	}
	void del_head() {
		if (head) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		} 
		else throw std::out_of_range("There are no elements in this List");
	}
	void del(int ind) { //delete an element fron the specified position
		if (ind == 0) del_head();
		else del(get(ind-1));
	}
	T& getvalue(int ind) {
		if (head) return get(ind)->data;
		else throw std::out_of_range("There are fewer elements in this List");
	}
};