#pragma once
#include <iostream>
#include <cstdlib>
#include <exception>
#include "stack.h"

using namespace std;
template <typename U, typename V>
class UV_RBT
{
private:
	class Node
	{
	public:
		Node* l, * r;
		bool is_red;
		V* data;
		U* key;
		Node(const U& ky, const V& d) : l(nullptr), r(nullptr), is_red(true)
		{
			key = new U(ky);
			data = new V(d);
		}

		Node() : key(nullptr), data(nullptr), l(nullptr), r(nullptr), is_red(true) {}

		~Node()
		{
			delete data;
			delete key;
			r = l = nullptr;
		}
	};
	Node* root;
	TStack <Node*> way;
	void right_rotate(Node* x, Node* parent_of_x)
	{
		Node* y = x->l;
		x->l = y->r;
		y->r = x;
		if (parent_of_x->l == x)
			parent_of_x->l = y;
		else parent_of_x->r = y;
	}
	void left_rotate(Node* x, Node* parent_of_x)
	{
		Node* y = x->r;
		x->r = y->l;
		y->l = x;
		if (parent_of_x->l == x)
			parent_of_x->l = y;
		else parent_of_x->r = y;
	}
	Node* return_brother(Node* father, Node* son_1)
	{
		if (father->l == son_1)
			return father->r;
		else if (father->r == son_1)
			return father->l;
		else return nullptr;
	}
public:
	UV_RBT()
	{
		root = new Node();
		root->is_red = false;
	}
	void insert(const U& ky, const V& dat)
	{
		if (root->l == nullptr && root->r == nullptr && root->key == nullptr)
		{
			root->data = new V(dat);
			root->key = new U(ky);
			return;
		}
		Node* parent = search_4_input(ky, true);
		if (*(parent->key) < ky)
			parent->r = new Node(ky, dat);
		else parent->l = new Node(ky, dat);

		if (way.quantElems()<2) return;

		way.pop();
		Node* grandpa = way.pop();
		Node* uncle = return_brother(grandpa, parent);

		while (parent->is_red)
		{
			if (uncle != nullptr && uncle->is_red)
			{
				parent->is_red = false;
				uncle->is_red = false;
				grandpa->is_red = true;
			}
			else //if there isn't an uncle or he is black
			{
				if (*(parent->key) > ky)					//if inserted is left
				{
					right_rotate(parent, grandpa);
					parent->is_red = false;
					grandpa->is_red = true;
					if (way.isEmpty()) break;
					left_rotate(grandpa, way.pop());
				}
				else									//if inserted is right
				{
					left_rotate(parent, grandpa);
					parent->is_red = false;
					grandpa->is_red = true;
					if (way.isEmpty()) break;
					right_rotate(grandpa, way.pop());
				}
				break;									//no need to check anymore
			}

			if (way.quantElems() < 2) break;
			parent = way.pop();
			grandpa = way.pop();
			uncle = return_brother(grandpa, parent);
			if (grandpa == root)
			{
				root->is_red = false;
				break;
			}
		}

		way.clear();
	}	
	void del(const U& ky)
	{
		if (*(root->key) == ky && root->l == nullptr && root->r == nullptr)
		{
			delete root;
			root = nullptr;
			return;
		}
		Node* x = search_vertex(ky, 1);
		Node* tmp, * parent, *grandparent, *brother;
		bool deleted_was_red;
		if (x->l == nullptr && x->r == nullptr)				//no chiidren
		{
			tmp = way.pop();
			if (tmp->l == x) tmp->l = nullptr;
			else tmp->r = nullptr;
			delete x;
			return;
		}
		else if (x->l == nullptr)							//one child
		{
			tmp = way.pop();
			if (tmp->l == x) { tmp->l = x->r; }
			else tmp->r = x->r;
			parent = tmp;
			tmp = tmp->r;
			deleted_was_red = x->is_red;
			delete x;
			if (deleted_was_red) return;
		}
		else if (x->r == nullptr)							//one child
		{
			tmp = way.pop();
			if (tmp->l == x) { tmp->l = x->l; }
			else tmp->r = x->l;
			parent = tmp;
			tmp = tmp->l;
			deleted_was_red = x->is_red;
			delete x;
			if (deleted_was_red) return;
		}
		else												//both children
		{
			way.push(x);
			tmp = x->r;
			while (tmp->l != nullptr)
			{
				way.push(tmp);
				tmp = tmp->l;
			}
			x->key = tmp->key;
			x->data = tmp->data;
			x = tmp;
			tmp = way.pop();
			tmp->l = x->r;
			parent = tmp;
			tmp = tmp->l;
			deleted_was_red = x->is_red;
			delete x;
			if (deleted_was_red) return;
		} //tmp contains a child of deleted vertex, parent - a parent of deleted vertex

		while (!tmp->is_red && tmp != root)
		{
			brother = return_brother(parent, tmp);
			if (brother->is_red)
			{
				grandparent = way.pop();
				left_rotate(parent, grandparent);
				brother->is_red = false;
				parent->is_red = true;
			}
			//brother is black
			brother = return_brother(parent, tmp);
			if (brother->l->is_red && brother->r->is_red)
			{
				brother->is_red = true;
				parent->is_red = false;
				return;
			}
			else if (brother->l->is_red && !brother->r->is_red)
			{
				brother->is_red = true;
				brother->l->is_red = false;
				right_rotate(brother, parent);
				brother = return_brother(parent, tmp);
			}
			if (brother->r->is_red)
			{
				brother->is_red = parent->is_red;
				parent->is_red = false;
				brother->r->is_red = false;
				left_rotate(parent, way.top());
				return;
			}
			tmp = parent;
			parent = way.pop();
		}

	}
	Node* search_4_input(const U& ky, bool need_to_fill_stack = false) //returns a parent of a leaf we must replase with Node(key). If a node with key exists, returns nullptr
	{
		Node* prev = root;
		way.clear();
		way.push(prev);
		while (true)
		{
			if (*(prev->key) == ky)
				return nullptr;
			else if (*(prev->key) < ky)
			{
				if (prev->r == nullptr)
					return prev;
				else prev = prev->r;
			}
			else /*if (prev->key > ky)*/
			{
				if (prev->l == nullptr)
					return prev;
				else prev = prev->l;
			}
			way.push(prev);
		}
	}
	Node* search_vertex(const U& ky, bool need_to_fill_stack = false) //returns V data if exists node with key == ky. Throws otherwise
	{
		Node* prev = root;
		if(need_to_fill_stack)	way.clear();
		while (true)
		{
			if (*(prev->key) == ky)
				return prev;
			else if (*(prev->key) < ky)
			{
				if (prev->r == nullptr)
					throw invalid_argument("There is no element with such key");
				else prev = prev->r;
			}
			else /*if (prev->key > ky)*/
			{
				if (prev->l == nullptr)
					throw invalid_argument("There is no element with such key");
				else prev = prev->l;
			}
			if (need_to_fill_stack)	way.push(prev);
		}
	}
	V& search(const U& ky)
	{
		return *(search_vertex(ky)->data);
	}
	bool avail(const U& ky)
	{
		Node* prev = root;
		if (root == nullptr || root->key == nullptr) return false;
		while (true)
		{
			if (*(prev->key) == ky)
				return true;
			else if (*(prev->key) < ky)
			{
				if (prev->r == nullptr)
					return false;
				else prev = prev->r;
			}
			else
			{
				if (prev->l == nullptr)
					return false;
				else prev = prev->l;
			}
		}
	}
};