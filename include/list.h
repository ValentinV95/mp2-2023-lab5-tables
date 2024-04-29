#ifndef LIST_H
#define LIST_H

#include <cassert>

// Односвязный список с фиктивной головой
template<class T>
class List
{
private:
	// Класс Node реализует элемент списка
	class Node
	{
	public:
		Node() : data(), next(nullptr) {}
		Node(const T& t) : data(t), next(nullptr) {}
		Node(T&& t) : data(std::move(t)), next(nullptr) {}
		T data;
		Node* next;
	};

	void _insert_after(Node* node, const T& t)
	{
		assert(node != nullptr && "Iterator is pointing at nullptr");
		Node* newnode = new Node(t);
		newnode->next = node->next;
		node->next = newnode;
	}

	void _erase_after(Node* node)
	{
		assert(node != nullptr && "Iterator is pointing at nullptr");
		Node* tmp = node->next;
		node->next = tmp->next;
		delete tmp;
	}

	Node* head;
	size_t sz;

public:
	class iterator
	{
	public:
		iterator(Node* n) : node(n) {}
		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int) { iterator it = *this; ++(*this); return it; }

		bool operator==(const iterator& it) { return node == it.node; }
		bool operator!=(const iterator& it) { return node != it.node; }

		T& operator*() const { assert(node != nullptr && "Iterator is pointing at nullptr"); return node->data; }
		T* operator->() const { assert(node != nullptr && "Iterator is pointing at nullptr"); return &(node->data); }

		friend class List;

	private:
		Node* node;
	};

	class const_iterator
	{
	public:
		const_iterator(Node* n) : node(n) {}
		const_iterator(const iterator& it) : node(it.node) {}
		const_iterator& operator++() { node = node->next; return *this; }
		const_iterator operator++(int) { const_iterator it = *this; ++(*this); return it; }

		bool operator==(const const_iterator& it) { return node == it.node; }
		bool operator!=(const const_iterator& it) { return node != it.node; }

		const T& operator*() const { assert(node != nullptr && "Iterator is pointing at nullptr"); return node->data; }
		const T* operator->() const { assert(node != nullptr && "Iterator is pointing at nullptr"); return &(node->data); }

		friend class List;

	private:
		Node* node;
	};

	List() : sz(0) { head = new Node(); }

	List(const List<T>& l) : sz(l.sz)
	{
		head = new Node(l.head->data);

		for (Node* ptr = head, *ptr_l = l.head->next; ptr_l != nullptr; ptr = ptr->next, ptr_l = ptr_l->next)
			ptr->next = new Node(ptr_l->data);
	}

	List(List<T>&& l) noexcept : sz(0)
	{
		head = new Node();
		swap(*this, l);
	}

	~List() { clear(); }

	List& operator=(const List<T>& l)
	{
		if (this == &l)
			return *this;
		List<T> tmp(l);
		swap(*this, tmp);
		return *this;
	}

	List& operator=(List<T>&& l) noexcept
	{
		if (this == &l)
			return *this;
		List<T> tmp(std::move(l));
		swap(*this, tmp);
		return *this;
	}

	friend void swap(List& lhs, List& rhs) noexcept
	{
		std::swap(lhs.head, rhs.head);
		std::swap(lhs.sz, rhs.sz);
	}

	// Полное удаление всех элементов из списка
	void clear()
	{
		for (Node* ptr = head; ptr != nullptr; )
		{
			Node* tmp = ptr->next;
			delete ptr;
			ptr = tmp;
		}

		head = nullptr;
		sz = 0;
	}

	// Добавление элемента в начало списка
	void insert(const T& t)
	{
		Node* node = new Node(t);
		Node* tmp = head->next;
		node->next = tmp;
		head->next = node;
		sz++;
	}

	// Добавление элемента в начало списка
	void insert(T&& t)
	{
		Node* node = new Node(std::move(t));
		Node* tmp = head->next;
		node->next = tmp;
		head->next = node;
		sz++;
	}

	// Добавляет в список значение, указанное итератором pos
	void insertAfter(const_iterator pos, const T& t) { _insert_after(pos.node, t); sz++; }

	// Удаляет из списка значение, указанное итератором pos
	void eraseAfter(const_iterator pos) { _erase_after(pos.node); sz--; }

	// Удаляет элемент из начала списка
	void pop()
	{
		Node* tmp = head->next;
		delete head;
		head = tmp;
		sz--;
	}

	bool isEmpty() const noexcept { return sz == 0; } // Проверяет, пуст ли список
	size_t size() const noexcept { return sz; } // Возвращает размер списка

	// Поэлементное сравнение списков
	bool operator==(const List<T>& l) const noexcept
	{
		if (sz != l.sz) return false;

		Node* tmp1 = head->next;
		Node* tmp2 = l.head->next;

		for (; tmp1 != nullptr; tmp1 = tmp1->next, tmp2 = tmp2->next)
			if (tmp1->data != tmp2->data) return false;
		return true;
	}

	bool operator!=(const List<T>& l) const noexcept { return !(*this == l); } // Поэлементное сравнение списков

	// Переворачивает список
	List reversed()
	{
		List tmp;
		for (Node* node = head->next; node != nullptr; node = node->next) tmp.insert(node->data);
		return tmp;
	}

	iterator before_begin() { return iterator(head); } // фиктивная голова
	const_iterator before_begin() const { return const_iterator(head); } // фиктивная голова
	const_iterator cbefore_begin() const { return const_iterator(head); } // фиктивная голова

	iterator begin() { return iterator(head->next); } // начало списка
	const_iterator begin() const { return const_iterator(head->next); } // начало списка
	const_iterator cbegin() const { return const_iterator(head->next); } // начало списка

	iterator end() { return iterator(nullptr); } // фиктивный хвост
	const_iterator end() const { return const_iterator(nullptr); } // фиктивный хвост
	const_iterator cend() const { return const_iterator(nullptr); } // фиктивный хвост
};

#endif //LIST_H