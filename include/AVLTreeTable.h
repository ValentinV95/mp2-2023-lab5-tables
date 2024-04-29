#pragma once
#include "poly.h"
#include <vector>

static int counttree = 0;
class AVLTreeTable {
	class Node {
	public:
		std::pair<std::string, polynoms> data;
		Node* left;
		Node* right;
		int h = 0;
		Node(std::string name, polynoms pol);
		
	};
	Node* head;
	Node* sh(std::string name);
	void TreeDestr(Node*& delv);
	void seth(Node* x);

public:
	AVLTreeTable();
	~AVLTreeTable();
	polynoms search(std::string name);
	std::vector<Node*> memorysearch(std::string name);
	int balance(Node* nd);
	void smallleftrot(Node* xparent, Node* x);
	void smallrightrot(Node* xparent, Node* x);
	void bigleftrot(Node* xparent, Node* x);
	void bigrightrot(Node* xparent, Node* x);
	void add(std::string name, polynoms pol);
	void clear(std::string name);
	polynoms Arithmetic(std::string strexpr);
};