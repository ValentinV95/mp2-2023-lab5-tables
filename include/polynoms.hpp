#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
inline void get_var(T &var) {
	std::string buf;
	std::cin >> var;
	std::cin.clear();
	std::getline(std::cin, buf);
}

const double eps = 1e-6;
const size_t VARS = 3;

class Monom;

template <typename T>
class List {
public:
	friend void merging(List<Monom> &list, size_t l, size_t m, size_t r);
	List() : head(nullptr), tail(nullptr), size(0) {}
	~List();
	List(const List<T> &c);
	List &operator=(const List<T> &c);
	bool operator==(const List<T> &c) const noexcept;
	bool operator!=(const List<T> &c) const noexcept { return !(*this == c); }
	T &operator[](size_t index) const { return get_node(index)->value; }
	size_t get_size() const noexcept { return size; }
	void push_back(const T &value) {
		if (size == 0) {
			tail = new Node(value, nullptr, nullptr);
			head = tail;
		}
		else {
			tail->next = new Node(value, nullptr, tail);
			tail = tail->next;
		}
		size++;
	}
	void push_front(const T &value) {
		if (size == 0) {
			head = new Node(value, nullptr, nullptr);
			tail = head;
		}
		else {
			head->prev = new Node(value, head, nullptr);
			head = head->prev;
		}
		size++;
	}
	T pop_back();
	T pop_front();
	void push(size_t index, const T &value);
	T pop(size_t index);
	class iterator;

private:
	class Node {
	public:
		Node(const T& inpvalue, Node *inpnext, Node *inpprev) : value(inpvalue), next(inpnext), prev(inpprev) {}
		T value;
		Node *next;
		Node *prev;
	};
	Node *get_node(size_t index) const {
		if (index >= size) {
			throw std::out_of_range("List out of bounds");
		}
		if (2 * index > size) {
			Node *curnode = tail;
			for (size_t i = size - 1; i > index; i--) {
				curnode = curnode->prev;
			}
			return curnode;
		}
		else {
			Node *curnode = head;
			for (size_t i = 0; i < index; i++) {
				curnode = curnode->next;
			}
			return curnode;
		}
	}
	Node *head;
	Node *tail;
	size_t size;
};

template <typename T>
class List<T>::iterator {
public:
	iterator(const List<T> &list, size_t index = 0) {
		if (list.get_size() != 0) {
			iternode = list.get_node(index);
		}
		else {
			iternode = nullptr;
		}
	};
	T &operator*() {
		return iternode->value;
	}
	iterator &operator++(int) {
		iterator old(*this);
		if (iternode != nullptr) {
			iternode = iternode->next;
		}
		return old;
	}
	iterator &operator--() {
		if (iternode != nullptr) {
			iternode = iternode->prev;
		}
		return *this;
	}
	bool is_end() {
		return (iternode == nullptr);
	}
private:
	List<T>::Node *iternode;
};

// Monom - const*x^n*y^m*z^p (n,m,p 0-9)

class Monom {
public:
	Monom() : coef(0.0) {
		for (size_t i = 0; i < VARS; i++) {
			degs[i] = 0;
		}
	}
	Monom(double inpcoef, const char *inpdegs);
	Monom(double inpcoef, unsigned int inpdegs);
	Monom(const Monom &c) = default;
	Monom(Monom && c) = default;
	Monom &operator=(const Monom &c) = default;
	Monom &operator=(Monom &&c) = default;
	friend std::ostream &operator<<(std::ostream &stream, const Monom &m);
	bool can_sum(const Monom &sec) const noexcept;
	int get_degs() const noexcept {
		int res = 0;
		for (size_t i = 0; i < VARS; i++) {
			res *= 10;
			res += static_cast<int>(degs[i]);
		}
		return res;
	}
	void set_degs(unsigned int inpdegs) {
		if (inpdegs >= std::pow(10, VARS)) {
			throw std::invalid_argument("Invalid degs number");
		}
		for (size_t i = 0; i < VARS; i++) {
			degs[VARS - i - 1] = inpdegs % 10;
			inpdegs /= 10;
		}
	}
	double get_coef() const noexcept { return coef; }
	void set_coef(double num) noexcept { coef = num; }
	Monom operator*(const Monom &sec) const;
	Monom operator*(double num) const { return Monom(coef * num, degs); }
	Monom operator-() const noexcept { return Monom(-coef, degs); }
	bool operator==(const Monom &sec) const noexcept;
	bool operator!=(const Monom &sec) const noexcept { return !(*this == sec); }
private:
	double coef;
	char degs[VARS];
};

class Polynom {
public:
	Polynom() : monoms() {}
	Polynom(const Monom& monom) : monoms() {
		monoms.push_back(monom);
	}
	Polynom(const List<Monom> &inpmonoms);
	bool operator==(const Polynom &sec) const noexcept {
		return (monoms == sec.monoms);
	}
	bool operator!=(const Polynom &sec) const noexcept {
		return (monoms != sec.monoms);
	}
	Polynom operator+(const Polynom &sec) const;
	Polynom operator-(const Polynom &sec) const {
		return (*this + sec * (-1.0));
	}
	Polynom operator*(const Polynom &sec) const;
	Polynom operator*(const Monom &sec) const {
		Polynom res(*this);
		List<Monom>::iterator curnode(res.monoms);
		for (size_t i = 0; i < res.monoms.get_size(); i++) {
			*curnode = (*curnode) * sec;
			curnode++;
		}
		return res;
	}
	Polynom operator*(double num) const {
		if (std::abs(num) < eps) {
			throw std::invalid_argument("Zero is not valid const");
		}
		Polynom res(*this);
		List<Monom>::iterator curnode(res.monoms);
		for (size_t i = 0; i < res.monoms.get_size(); i++) {
			*curnode = (*curnode) * num;
			curnode++;
		}
		return res;
	}
	friend std::ostream &operator<<(std::ostream &stream, const Polynom &poly);
private:
	List<Monom> monoms;
};

template <typename T>
List<T>::List(const List<T> &c) : size(c.size) {
	if (size == 0) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = new Node(c.head->value, nullptr, nullptr);
		Node *curnode = c.head->next;
		Node *prevnode = head;
		while (curnode != nullptr) {
			prevnode->next = new Node(curnode->value, nullptr, prevnode);
			prevnode = prevnode->next;
			curnode = curnode->next;
		}
		tail = prevnode;
	}
}

template <typename T>
List<T>::~List() {
	if (size > 0) {
		Node *curnode = head;
		while (curnode->next != nullptr) {
			curnode = curnode->next;
			delete curnode->prev;
		}
		delete curnode;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &c) {
	if (&c == this) {
		return *this;
	}
	if (size > 0) {
		Node *curnode = head;
		while (curnode->next != nullptr) {
			curnode = curnode->next;
			delete curnode->prev;
		}
		delete curnode;
	}
	size = c.size;
	if (size == 0) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = new Node(c.head->value, nullptr, nullptr);
		Node *curnode = c.head->next;
		Node *prevnode = head;
		while (curnode != nullptr) {
			prevnode->next = new Node(curnode->value, nullptr, prevnode);
			prevnode = prevnode->next;
			curnode = curnode->next;
		}
		tail = prevnode;
	}
	return *this;
}

template <typename T>
bool List<T>::operator==(const List<T> &c) const noexcept {
	if (size != c.size) {
		return false;
	}
	Node *ptr1 = head;
	Node *ptr2 = c.head;
	while (ptr1 != nullptr) {
		if (ptr1->value != ptr2->value) {
			return false;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	return true;
}

template <typename T>
T List<T>::pop_back() {
	T res;
	if (size == 0) {
		throw std::runtime_error("Pop empty list");
	}
	else if (size == 1) {
		res = tail->value;
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	else {
		res = tail->value;
		Node *prevtail = tail->prev;
		prevtail->next = nullptr;
		delete tail;
		tail = prevtail;
	}
	size--;
	return res;
}

template <typename T>
T List<T>::pop_front() {
	T res;
	if (size == 0) {
		throw std::runtime_error("Pop empty list");
	}
	else if (size == 1) {
		res = head->value;
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		res = head->value;
		Node *nexthead = head->next;
		nexthead->prev = nullptr;
		delete head;
		head = nexthead;
	}
	size--;
	return res;
}

template <typename T>
void List<T>::push(size_t index, const T &value) {
	if (index == 0) {
		push_front(value);
	}
	else if (index == size) {
		push_back(value);
	}
	else {
		Node *curnode = get_node(index);
		Node *newnode = new Node(value, curnode, curnode->prev);
		curnode->prev->next = newnode;
		curnode->prev = newnode;
		size++;
	}
}

template <typename T>
T List<T>::pop(size_t index) {
	T res;
	if (index == 0) {
		res = pop_front();
	}
	else if (size != 0 && index == size-1) {
		res = pop_back();
	}
	else {
		Node *curnode = get_node(index);
		res = curnode->value;
		curnode->prev->next = curnode->next;
		curnode->next->prev = curnode->prev;
		delete curnode;
		size--; 
	}
	return res;
}

void merging(List<Monom> &list, size_t l, size_t m, size_t r);
void merge_sorting(List<Monom> &list, size_t l, size_t r);
Polynom fill_polynom();
