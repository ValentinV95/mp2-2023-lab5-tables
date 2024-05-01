#pragma once
#include "poly.h"


class HashTable {
	class Rec {
	public:
		std::pair<std::string, polynoms> data;
		int state; //-1 - deleted, 0 - null, 1 - contented
		Rec(std::string name, polynoms pol);
	};
	Rec** table;
	size_t size;
	size_t placed;
	int Hash1(std::string name);
	int Hash2(std::string name);
	Rec* sh(std::string& name);
	bool isPrime(int num);
	int nextPrimeAfter(int n);
	void resize();
public:
	HashTable();
	~HashTable();
	HashTable(const HashTable& other);
	polynoms search(std::string& name);
	void add(std::string name, polynoms pol);
	void clear(std::string name);
	polynoms Arithmetic(std::string strexpr);
	int counthash = 0;
};