#include "arithmetic.h"
#include "HashTable.h"
HashTable::Rec::Rec(std::string name, polynoms pol) {
	data = make_pair(name, pol);
	state = 1;
}


int HashTable:: Hash1(std::string name) {
	counthash++;
	int res, strsum = 0;
	for (int i = 0; i < name.size(); i++) {
		strsum += int(name[i]);
	}
	res = strsum % size;
	return res;
}
int HashTable::Hash2(std::string name) {
	counthash++;
	int res, strsum = 0;
	for (int i = 0; i < name.size(); i++) {
		strsum += int(name[i]);
	}
	res = 1 + strsum % (size - 1);
	return res;
}
HashTable::Rec* HashTable:: sh(std::string name) {
	for (int i = 0; i < size; i++) {
		counthash++;
		if (table[(Hash1(name) + i * Hash2(name)) % size]) {
			if (table[(Hash1(name) + i * Hash2(name)) % size]->data.first == name) {
				return table[(Hash1(name) + i * Hash2(name)) % size];
			}
		}
	}
	return nullptr;
}
bool HashTable:: isPrime(int num) {
	if (num <= 1) {
		return false;
	}
	for (int i = 2; i * i <= num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int HashTable:: nextPrimeAfter(int n) {
	int nextNum = n * 2 + 1;
	while (true) {
		if (isPrime(nextNum)) {
			return nextNum;
		}
		nextNum++;
	}
}

HashTable:: HashTable() {
	size = 3;
	placed = 0;
	table = new Rec * [size];
	for (int i = 0; i < size; i++) {
		table[i] = nullptr;
	}
}
HashTable:: ~HashTable() {
	for (int i = 0; i < size; i++)
		if (table[i])
			delete table[i];
	delete[] table;
}
HashTable::HashTable(const HashTable& other) {
	size = other.size;
	placed = other.placed;
	table = new Rec * [size];
	for (size_t i = 0; i < size; ++i) {
		if (other.table[i] != nullptr) {
			table[i] = new Rec(other.table[i]->data.first, other.table[i]->data.second);
			table[i]->state = other.table[i]->state;
		}
		else {
			table[i] = nullptr;
		}
	}
}

polynoms HashTable::search(std::string name) {
	counthash = 0;
	Rec* tmp = sh(name);
	if (tmp && tmp->state==1) {
		return sh(name)->data.second;
	}
	throw std::logic_error("No such element in table");
}
void HashTable::add(std::string name, polynoms pol) {
	counthash = 0;

	if (placed == size) resize();
	if (table[Hash1(name)] == nullptr) {
		table[Hash1(name)] = new Rec(name, pol);
		placed++;
		counthash++;
		return;
	}
	for (int i = 0; i < size; i++) {
		counthash++;
		if (table[(Hash1(name) + i * Hash2(name)) % size] != nullptr) {
			if (table[(Hash1(name) + i * Hash2(name)) % size]->state == 0 || table[(Hash1(name) + i * Hash2(name)) % size]->state == -1) {
				table[(Hash1(name) + i * Hash2(name)) % size] = new Rec(name, pol);
				return;
			}
			if (table[(Hash1(name) + i * Hash2(name)) % size]->state == 1) {
				continue;
			}
		}
		if (table[(Hash1(name) + i * Hash2(name)) % size] == nullptr) {
			table[(Hash1(name) + i * Hash2(name)) % size] = new Rec(name, pol);
			placed++;
			return;
		}
	}
}
void HashTable::clear(std::string name) {
	counthash = 0;
	Rec* tmp = sh(name);
	if (tmp) {
		tmp->state = -1;
	}
	counthash++;
	return;
}
void HashTable:: resize() {
	int n = nextPrimeAfter(size);
	Rec** newtable = new Rec * [n];
	for (int i = 0; i < n; i++) {
		newtable[i] = nullptr;
	}
	for (int j = 0; j < size; j++) {
		counthash++;
		if (newtable[Hash1(table[j]->data.first)] == nullptr) {
			newtable[Hash1(table[j]->data.first)] = new Rec(table[j]->data.first, table[j]->data.second);
			continue;
		}
		for (int i = 0; i < size; i++) {
			counthash++;
			if (newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size]) {
				if (newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size]->state == 0 || newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size]->state == -1) {
					newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size] = new Rec(table[i]->data.first, table[i]->data.second);

				}
				if (newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size]->state == 1) {
					continue;
				}
			}
			if (newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size] == nullptr) {
				newtable[(Hash1(table[i]->data.first) + i * Hash2(table[i]->data.first)) % size] = new Rec(table[i]->data.first, table[i]->data.second);
				break;
			}
		}
	}
	delete[] table;
	table = newtable;
	size = n;
}
polynoms HashTable:: Arithmetic(std::string strexpr) {
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


