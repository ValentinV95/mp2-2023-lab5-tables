// rbt.h contains template class for a red-black tree

#ifndef RBT_H
#define RBT_H

#include <stack>
#include <queue>
#include "table_rec.h"

template<class T>
class rbtree
{
public:
	rbtree() : sz(0), head(nullptr) {}

	rbtree(const rbtree& t) : sz(t.sz), head(nullptr) { _copyInOrder(head, t.head); }

	~rbtree()
	{
		if (head == nullptr)
			return;

		std::queue<Node*> qe;
		qe.push(head);

		while (!qe.empty())
		{
			Node* tmp = qe.front();

			if (tmp->l != nullptr)
				qe.push(tmp->l);
			if (tmp->r != nullptr)
				qe.push(tmp->r);

			delete qe.front();
			qe.pop();
		}
	}

	rbtree& operator=(const rbtree& t)
	{
		if (this == &t)
			return *this;
		rbtree tmp(t);
		std::swap(sz, tmp.sz);
		std::swap(head, tmp.head);
		return *this;
	}

	void insert(const std::string& key, const T& t)
	{
		Node* n = new Node(key, t);
		std::stack<Node*> path;

		if (head == nullptr)
			head = n;

		else
		{
			Node* tmp = head;

			while (true)
			{
				path.push(tmp);

				if (key < tmp->val.key)
				{
					if (tmp->l == nullptr) break;
					tmp = tmp->l;
				}

				else
				{
					if (tmp->r == nullptr) break;
					tmp = tmp->r;
				}
			}

			if (key < tmp->val.key)
				tmp->l = n;

			else
				tmp->r = n;
		}

		path.push(n);
		insert_case1(n, path);
		++sz;
	}

	void insert(TableRec<T>&& tr) { insert(tr.key, tr.val); }

	void remove(const std::string& key)
	{
		std::stack<Node*> path;
		Node* tmp = head;
		Node* p = nullptr;
		Node* next_node = nullptr;

		while (tmp != nullptr)
		{
			path.push(tmp);

			if (tmp->val.key == key)
				break;

			else
			{
				p = tmp;
				if (tmp->val.key < key)
					tmp = tmp->r;
				else
					tmp = tmp->l;
			}
		}

		if (tmp == nullptr) return;

		if (tmp->l == nullptr && tmp->r == nullptr)
		{
			bool fl = false;
			if (p != nullptr)
			{
				if (p->l == tmp)
					fl = true;

				if (!tmp->red)
					remove_case1(tmp, path);

				if (fl)
					p->l = nullptr;
				else
					p->r = nullptr;
			}

			else
				head = nullptr;

			delete tmp;
			tmp = nullptr;
		}

		else if (tmp->l == nullptr || tmp->r == nullptr)
		{
			bool fl = false;
			if (tmp->l != nullptr)
				next_node = tmp->l;
			else
				next_node = tmp->r;

			if (p != nullptr)
			{
				if (tmp == p->l)
					fl = true;

				if (!next_node->red)
					remove_case1(tmp, path);

				if (fl)
					p->l = next_node;
				else
					p->r = next_node;
			}

			else
				head = nullptr;

			delete tmp;
			tmp = nullptr;
		}

		else
		{
			std::stack<Node*> next = _getNext(key);
			next_node = next.top();
			Node* p_next = parent(next_node, next);
			bool fl = false;

			if (next_node == p_next->l)
				fl = true;

			if (tmp == head)
				head = tmp;

			swap(*next_node, *tmp);
			path = next;

			if (!next_node->red)
				remove_case1(next_node, path);

			delete next_node;
			next_node = nullptr;

			if (fl)
				p_next->l = nullptr;
			else
				p_next->r = nullptr;
		}

		sz--;
	}

	T* find(const std::string& key)
	{
		Node* tmp = head;

		while (tmp != nullptr)
		{
			if (key == tmp->val.key)
				return &(tmp->val.val);
			else if (key < tmp->val.key)
				tmp = tmp->l;
			else if (key > tmp->val.key)
				tmp = tmp->r;
		}

		return nullptr;
	}

	size_t size() { return sz; }
	bool empty() { return sz == 0; }

private:
	class Node
	{
	public:
		Node(const Node& n) : val(n.val), l(n.l), r(n.r), red(n.red) {}
		Node(const std::string& key, const T& t) : val(key, t), l(nullptr), r(nullptr), red(true) {}
		Node(TableRec<T>&& tr) : val(tr), l(nullptr), r(nullptr), red(true) {}
		Node(T&& t) : val(t), l(nullptr), r(nullptr), red(true) {}
		TableRec<T> val;
		Node* l;
		Node* r;
		bool red; // 0 for black, 1 for red
	};

	void insert_case1(Node*& n, std::stack<Node*>& st)
	{
		if (parent(n, st) == nullptr)
			n->red = false;
		else
			insert_case2(n, st);
	}

	void insert_case2(Node*& n, std::stack<Node*>& st)
	{
		if (!parent(n, st)->red)
			return;
		else
			insert_case3(n, st);
	}

	void insert_case3(Node*& n, std::stack<Node*>& st)
	{
		Node* u = uncle(n, st);

		if (u != nullptr && u->red)
		{
			parent(n, st)->red = false;
			u->red = false;
			Node* g = grandparent(n, st);
			g->red = true;
			st.pop();
			st.pop();
			insert_case1(g, st);
		}

		else
			insert_case4(n, st);
	}

	void insert_case4(Node*& n, std::stack<Node*>& st)
	{
		Node* g = grandparent(n, st);
		Node* p = parent(n, st);

		if (n == p->r && p == g->l)
		{
			rotateLeft(p, st);
			n = n->l;
		}

		else if (n == p->l && p == g->r)
		{
			rotateRight(p, st);
			n = n->r;
		}

		insert_case5(n, st);
	}

	void insert_case5(Node*& n, std::stack<Node*>& st)
	{
		Node* g = grandparent(n, st);
		Node* p = parent(n, st);

		p->red = false;
		g->red = true;

		if (n == p->l && p == g->l)
		{
			st.pop(); // because current st.top() is n, we have to pop it to make current node p and its parent g
			rotateRight(g, st);
		}

		else
		{
			st.pop();
			rotateLeft(g, st);
		}
	}

	void remove_case1(Node*& n, std::stack<Node*>& st)
	{
		if (n == head && n->red)
			return;

		Node* b = brother(n, st);
		Node* p = parent(n, st);

		if (b != nullptr && b->red)
		{
			if (n == p->l)
			{
				b->red = false;
				p->red = true;
				rotateLeft(p, st);
				st.push(n);
			}

			else
			{
				b->red = false;
				p->red = true;
				rotateRight(p, st);
				st.push(n);
			}
		}

		remove_case2(n, st);
	}

	void remove_case2(Node*& n, std::stack<Node*>& st)
	{
		Node* b = brother(n, st);

		if (
			(b->l == nullptr || !b->l->red) &&
			(b->r == nullptr || !b->r->red)
			)
		{
			b->red = true;
			Node* p = parent(n, st);

			if (p->red)
			{
				p->red = false;
				return;
			}

			st.pop();
			remove_case1(p, st);
		}

		else
			remove_case3(n, st);

	}

	void remove_case3(Node*& n, std::stack<Node*>& st)
	{
		Node* p = parent(n, st);
		Node* b = brother(n, st);

		if (n == p->l)
		{
			if (b->l != nullptr && b->l->red && (b->r == nullptr || !b->r->red))
			{
				b->red = true;
				b->l->red = false;

				// Need to do this to swap the pointers correctly
				st.pop();
				st.push(b);
				st.push(b->l);

				rotateRight(b, st);

				st.pop();
				st.pop();
				st.push(n);
			}
		}

		else
		{
			if (b->r != nullptr && b->r->red && (b->l == nullptr || !b->l->red))
			{
				b->red = true;
				b->r->red = false;

				st.pop();
				st.push(b);
				st.push(b->r);

				rotateLeft(b, st);

				st.pop();
				st.pop();
				st.push(n);
			}
		}

		remove_case4(n, st);
	}

	void remove_case4(Node*& n, std::stack<Node*>& st)
	{
		Node* p = parent(n, st);
		Node* b = brother(n, st);

		b->red = p->red;
		p->red = false;

		if (n == p->l)
		{
			b->r->red = false;
			rotateLeft(p, st);
		}

		else
		{
			b->l->red = false;
			rotateRight(p, st);
		}
	}

	Node* parent(Node* n, std::stack<Node*>& st)
	{
		if (st.size() > 1)
		{
			Node* tmp = st.top();
			st.pop();
			Node* p = st.top();
			st.push(tmp);
			return p;
		}

		return nullptr;
	}

	Node* brother(Node* n, std::stack<Node*>& st)
	{
		Node* p = parent(n, st);

		if (p == nullptr)
			return nullptr;
		else if (n == p->l)
			return p->r;
		else
			return p->l;
	}

	Node* grandparent(Node* n, std::stack<Node*>& st)
	{
		if (st.size() > 2)
		{
			Node* tmp1 = st.top();
			st.pop();
			Node* tmp2 = st.top();
			st.pop();
			Node* g = st.top();
			st.push(tmp2);
			st.push(tmp1);
			return g;
		}

		return nullptr;
	}

	Node* uncle(Node* n, std::stack<Node*>& st)
	{
		Node* g = grandparent(n, st);
		Node* p = parent(n, st);

		if (g == nullptr)
			return nullptr;
		else if (p == g->l)
			return g->r;
		else
			return g->l;
	}

	void rotateLeft(Node*& x, std::stack<Node*>& st)
	{
		Node* y = x->r;
		Node* p = grandparent(x, st);

		x->r = y->l;
		y->l = x;

		if (p == nullptr)
			head = y;
		else if (y->val < p->val)
			p->l = y;
		else
			p->r = y;

		st.pop();
		st.pop();
		st.push(y);
		st.push(x);
	}

	void rotateRight(Node*& x, std::stack<Node*>& st)
	{
		Node* y = x->l;
		Node* p = grandparent(x, st);

		x->l = y->r;
		y->r = x;

		if (p == nullptr)
			head = y;
		else if (y->val < p->val)
			p->l = y;
		else
			p->r = y;

		st.pop();
		st.pop();
		st.push(y);
		st.push(x);
	}

	// Gets the path to the next node in the tree
	std::stack<Node*> _getNext(const std::string& key)
	{
		std::stack<Node*> st;
		Node* tmp = head;
		Node* next = nullptr;

		while (tmp != nullptr)
		{
			st.push(tmp);
			if (tmp->val.key > key) { next = tmp; tmp = tmp->l; }
			else tmp = tmp->r;
		}

		return st;
	}

	Node* _copyInOrder(Node*& n, Node* cn)
	{
		if (cn == nullptr)
			return nullptr;

		n = new Node(*cn);
		if (cn->l != nullptr)
			_copyInOrder(n->l, cn->l);
		if (cn->r != nullptr)
			_copyInOrder(n->r, cn->r);
	}

	friend void swap(Node& rhs, Node& lhs)
	{
		std::swap(rhs.val, lhs.val);
	}

	Node* head;
	size_t sz;
};

#endif