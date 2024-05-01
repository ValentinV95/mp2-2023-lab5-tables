#pragma once
#include "Polynom.h"


class HashTable {
	std::pair<short int, std::pair<std::string, Polynom>>* mas;
	// 0 - null, 1 - deleted, 2 - contented

	size_t capacity, q;

	size_t hash(const std::string& s) const noexcept;

	void rebuild();

public:
	HashTable();

	~HashTable();

	void add(const std::string& s, const Polynom& P);

	void add(const std::pair<std::string, Polynom>& pa);

	Polynom find(const std::string& s);

	void del(const std::string& s);

	size_t countoperations;
};