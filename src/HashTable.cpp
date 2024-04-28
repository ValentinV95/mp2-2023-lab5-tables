#include "HashTable.h"
#include <iostream>


size_t HashTable::hash(const std::string& s) const noexcept {
	size_t res = 0;
	for (size_t i = 0; i < s.size(); i++) {
		res += size_t(s[i]) * (i + 1);
	}
	return res % capacity;
};

void HashTable::rebuild() {
	std::pair<short int, std::pair<std::string, Polynom>>* mas2 = new std::pair<short int, std::pair<std::string, Polynom>> [capacity * 2 + 1] {};
	size_t tmp = capacity;
	capacity *= 2;
	capacity++;
	q *= 2;
	std::swap(mas, mas2);
	for (size_t i = 0; i < tmp; i++) add(mas2[i].second);
	delete[] mas2;
};

HashTable::HashTable() {
	capacity = 15;
	q = 2;
	mas = new std::pair<short int, std::pair<std::string, Polynom>>[capacity] {};
};

HashTable::~HashTable() {
	delete[] mas;
	mas = nullptr;
};

void HashTable::add(const std::string& s, const Polynom& P) {
	try {
		find(s);
	}
	catch (std::exception& e) {
		size_t h = hash(s);
		while (mas[h].first == 2) {
			do {
				h =(h + q) % capacity;
			} while (mas[h].first==2 && h != hash(s));

			if (mas[h].first==2 && h == hash(s)) {
				rebuild();
				h = hash(s);
			};
		};
		mas[h] = std::pair<short int, std::pair<std::string, Polynom>>(2, std::pair<std::string, Polynom>(s, P));
		return;
	}
	throw std::invalid_argument("You already saved a polynom in this table by this key");
};

void HashTable::add(const std::pair<std::string, Polynom>& pa) {
	add(pa.first, pa.second);
};

Polynom HashTable::find(const std::string& s) const {
	size_t h = hash(s);
	do {
		if (mas[h].second.first == s && mas[h].first == 2) return mas[h].second.second;
		else h = (h + q) % capacity;
	} while (h != hash(s) && mas[h].first);
	throw std::invalid_argument("There are no such key in this table");
};

void HashTable::del(const std::string& s) {
	size_t h = hash(s);
	do {
		if (mas[h].second.first == s && mas[h].first == 2) {
			mas[h].first = 1;
			return;
		}
		else h = (h + q) % capacity;
	} while (h != hash(s) && mas[h].first);
};