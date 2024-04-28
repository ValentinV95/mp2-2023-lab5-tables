#pragma once
#include "Polynom.h"


class HashTable {
	std::pair<short int, std::pair<std::string, Polynom>>* mas;

	size_t capacity, q;

	size_t hash(const std::string& s) const noexcept;

	void rebuild();

public:
	HashTable();

	~HashTable();

	void add(const std::string& s, const Polynom& P);

	void add(const std::pair<std::string, Polynom>& pa);

	Polynom find(const std::string& s) const;

	void del(const std::string& s);
};