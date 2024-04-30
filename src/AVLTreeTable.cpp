
#include "AVLTreeTable.h"
#include "arithmetic.h"


AVLTreeTable::Node::Node(std::string name, polynoms pol) {
	data = std::make_pair(name, pol);
	left = nullptr;
	right = nullptr;
}


AVLTreeTable::Node* AVLTreeTable::sh(std::string name) {
	Node* cur = head;
	while (cur) {
		if (cur->data.first == name) {
			return cur;
		}
		if (name > cur->data.first) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}
	throw std::logic_error("No such element is in table");
}
void AVLTreeTable::TreeDestr(Node*& delv)
{
	if (delv != nullptr)
	{
		TreeDestr(delv->left);
		TreeDestr(delv->right);
		delete delv;
		delv = nullptr;
	}
}
void AVLTreeTable:: seth(Node* x) {
	counttree++;
	if (x->left && x->right) {
		x->h = 1 + std::max(x->left->h, x->right->h);
	}
	else if (x->left && !x->right) {
		x->h = 1 + x->left->h;
	}
	else if (!x->left && x->right) {
		x->h = 1 + x->right->h;
	}
	else {
		x->h = 0;
	}
}

AVLTreeTable::AVLTreeTable() : head(nullptr) {}
AVLTreeTable::~AVLTreeTable() { TreeDestr(head); }

polynoms AVLTreeTable::search(std::string name) {
	counttree = 0;
	Node* cur = sh(name);
	return cur->data.second;
}
std::vector<AVLTreeTable::Node*> AVLTreeTable::memorysearch(std::string name) {
	Node* cur = head;
	std::vector<Node*> path;
	while (cur) {
		counttree++;
		if (cur->data.first == name) {
			path.push_back(cur);
			break;
		}
		if (name > cur->data.first) {
			path.push_back(cur);
			cur = cur->right;
		}
		else {
			path.push_back(cur);
			cur = cur->left;
		}
	}
	return path;
}
int AVLTreeTable::balance(Node* nd) {
	counttree++;
	if (nd->left == nullptr && nd->right == nullptr) {
		return 0;
	}
	else if (nd->left == nullptr && nd->right) {
		return -(nd->right->h + 1);
	}
	else if (nd->left && nd->right == nullptr) {
		return nd->left->h + 1;
	}
	else if (nd->left && nd->right) {
		return nd->left->h - nd->right->h;
	}



};
void AVLTreeTable::smallleftrot(Node* xparent, Node* x) {
	counttree++;
	bool left;
	if (xparent && xparent->left && xparent->left == x) {
		left = true;
	}
	else if (xparent && xparent->right == x) {
		left = false;
	}
	Node* y = x->right;
	x->right = y->left;
	y->left = x;
	if (xparent == nullptr) {
		head = y;
		seth(x);
		seth(y);
		return;
	}
	if (left) {
		xparent->left = y;
	}
	else {
		xparent->right = y;
	}
	seth(x);
	seth(y);
}
void AVLTreeTable:: smallrightrot(Node* xparent, Node* x) {
	counttree++;
	bool left;
	if (xparent && xparent->left && xparent->left == x) {
		left = true;
	}
	else if (xparent && xparent->right == x) {
		left = false;
	}
	Node* y = x->left;
	x->left = y->right;
	y->right = x;
	if (xparent == nullptr) {
		head = y;
		seth(x);
		seth(y);
		return;
	}
	if (left) {
		xparent->left = y;
	}
	else {
		xparent->right = y;
	}
	seth(x);
	seth(y);
}
void AVLTreeTable::bigleftrot(Node* xparent, Node* x) {
	counttree++;
	bool left;
	if (xparent && xparent->left && xparent->left == x) {
		left = true;
	}
	else if (xparent && xparent->right == x) {
		left = false;
	}
	Node* y = x->right;
	Node* z = y->left;
	x->right = z->left;
	y->left = z->right;
	z->left = x;
	z->right = y;
	if (xparent == nullptr) {
		head = z;
		seth(x);
		seth(y);
		seth(z);
		return;
	}
	if (left) {
		xparent->left = z;
	}
	else {
		xparent->right = z;
	}
	seth(x);
	seth(y);
	seth(z);
}
void AVLTreeTable:: bigrightrot(Node* xparent, Node* x) {
	counttree++;
	bool left;
	if (xparent && xparent->left && xparent->left == x) {
		left = true;
	}
	else if (xparent && xparent->right == x) {
		left = false;
	}
	Node* y = x->left;
	Node* z = y->right;
	y->right = z->left;
	x->left = z->right;
	z->left = y;
	z->right = x;
	if (xparent == nullptr) {
		head = z;
		seth(x);
		seth(y);
		seth(z);
		return;
	}
	if (left) {
		xparent->left = z;
	}
	else {
		xparent->right = z;
	}
	seth(x);
	seth(y);
	seth(z);
}

void AVLTreeTable::add(std::string name, polynoms pol) {
	counttree = 0;
	if (head == nullptr) {
		counttree++;
		head = new Node(name, pol);
	}
	try {
		search(name);
	}
	catch (std::logic_error& e) {
		Node* cur = head;
		std::vector<Node*> path = memorysearch(name);
		while (true) {
			counttree++;
			if (name < cur->data.first) {
				if (cur->left) {
					cur->h += 1;
					cur = cur->left;
				}
				else {
					break;
				}
			}
			else {
				if (cur->right) {
					cur->h += 1;
					cur = cur->right;
				}
				else {
					break;
				}
			}
		}
		counttree++;
		if (name < cur->data.first) {
			cur->left = new Node(name, pol);
		}
		else {
			cur->right = new Node(name, pol);
		}
		for (int i = path.size() - 1; i >= 0; i--) {
			counttree++;
			if (path[i]->left == nullptr && path[i]->right == nullptr) {
				path[i]->h = 0;
			}
			else if (path[i]->left != nullptr && path[i]->right == nullptr) {

				if (balance(path[i]) == 2) {
					if (balance(path[i]->left) >= 0) {
						if (i == 0) smallrightrot(nullptr, path[i]);
						else smallrightrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->left) < 0) {
						if (i == 0) bigrightrot(nullptr, path[i]);
						else bigrightrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}
			else if (path[i]->left == nullptr && path[i]->right != nullptr) {

				if (balance(path[i]) == -2) {
					if (balance(path[i]->right) <= 0) {
						if (i == 0) smallleftrot(nullptr, path[i]);
						else smallleftrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->right) > 0) {
						if (i == 0) bigleftrot(nullptr, path[i]);
						else bigleftrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}
			else {

				if (balance(path[i]) == 2) {
					if (balance(path[i]->left) >= 0) {
						if (i == 0) smallrightrot(nullptr, path[i]);
						else smallrightrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->left) < 0) {
						if (i == 0) bigrightrot(nullptr, path[i]);
						else bigrightrot(path[i - 1], path[i]);
					}
				}
				if (balance(path[i]) == -2) {
					if (balance(path[i]->right) <= 0) {
						if (i == 0) smallleftrot(nullptr, path[i]);
						else smallleftrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->right) > 0) {
						if (i == 0) bigleftrot(nullptr, path[i]);
						else bigleftrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}

		}

	}
}

void AVLTreeTable::clear(std::string name) {
	counttree = 0;
	try {
		search(name);

		std::vector<Node*> path = memorysearch(name);
		if (path[path.size() - 1]->h == 0) { //leaf
			counttree++;
			if (path.size() == 1) { //only head
				head = nullptr;
				delete path[0];
			}
			else if (path[path.size() - 2]->left == path[path.size() - 1]) {
				path[path.size() - 2]->left = nullptr;
				delete path[path.size() - 1];
			}
			else if (path[path.size() - 2]->right == path[path.size() - 1]) {
				path[path.size() - 2]->right = nullptr;
				delete path[path.size() - 1];
			}
		}
		else {
			counttree++;
			Node* cur = path[path.size() - 1];
			if (cur->right) {
				counttree++;
				Node* delnd = cur;
				cur = cur->right;
				path.push_back(cur);
				while (cur->left) {
					counttree++;
					cur = cur->left;
					path.push_back(cur);
				}
				Node* minval = path[path.size() - 1], * tmp = delnd;
				delnd->data = minval->data;
				minval->data = tmp->data;
				if (minval->left == nullptr && minval->right == nullptr) {
					counttree++;
					if (path[path.size() - 2]->left == minval) {
						path[path.size() - 2]->left = nullptr;
					}
					else {
						path[path.size() - 2]->right = nullptr;
					}
				}
				else if (minval->left == nullptr && minval->right != nullptr) {
					path[path.size() - 2]->right == minval->right;
					counttree++;
				}
				else if (minval->left != nullptr && minval->right == nullptr) {
					path[path.size() - 2]->right == minval->left;
					counttree++;
				}
				delete minval;

			}
			else {
				counttree++;
				if (path[path.size() - 2]->left == cur) {
					path[path.size() - 2]->left = cur->left;
				}
				else {
					path[path.size() - 2]->right = cur->left;
				}
			}
		}
		for (int i = path.size() - 2; i >= 0; i--) {
			counttree++;
			if (path[i]->left == nullptr && path[i]->right == nullptr) {
				path[i]->h = 0;
			}
			else if (path[i]->left != nullptr && path[i]->right == nullptr) {

				if (balance(path[i]) == 2) {
					if (balance(path[i]->left) >= 0) {
						if (i == 0) smallrightrot(nullptr, path[i]);
						else smallrightrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->left) < 0) {
						if (i == 0) bigrightrot(nullptr, path[i]);
						else bigrightrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}
			else if (path[i]->left == nullptr && path[i]->right != nullptr) {

				if (balance(path[i]) == -2) {
					if (balance(path[i]->right) <= 0) {
						if (i == 0) smallleftrot(nullptr, path[i]);
						else smallleftrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->right) > 0) {
						if (i == 0) bigleftrot(nullptr, path[i]);
						else bigleftrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}
			else {

				if (balance(path[i]) == 2) {
					if (balance(path[i]->left) >= 0) {
						if (i == 0) smallrightrot(nullptr, path[i]);
						else smallrightrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->left) < 0) {
						if (i == 0) bigrightrot(nullptr, path[i]);
						else bigrightrot(path[i - 1], path[i]);
					}
				}
				if (balance(path[i]) == -2) {
					if (balance(path[i]->right) <= 0) {
						if (i == 0) smallleftrot(nullptr, path[i]);
						else smallleftrot(path[i - 1], path[i]);
					}
					else if (balance(path[i]->right) > 0) {
						if (i == 0) bigleftrot(nullptr, path[i]);
						else bigleftrot(path[i - 1], path[i]);
					}
				}
				seth(path[i]);

			}

		}

	}
	catch (std::logic_error& e) {
		return;
	}
}

polynoms AVLTreeTable:: Arithmetic(std::string strexpr) {
	ArithmeticExpr expr(strexpr);
	expr.ToPostfix();
	std::vector<std::string> operands = expr.GetOperands();
	std::map<std::string, polynoms> values;
	for (int i = 0; i < operands.size(); i++) {
		if (operands[i][0] < '0' || operands[i][0]>'9') {
			values[operands[i]] = search(operands[i]);
		}
	}
	polynoms res = expr.Calculate(values);
	return res;
}

