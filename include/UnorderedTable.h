#pragma once
#include "poly.h"
#include <vector>


class UnorderedTable {
	std::vector<std::pair<std::string, polynoms>> table;
	size_t size;
	
public:
	UnorderedTable();
	UnorderedTable(UnorderedTable& T);
	void add(std::string name, polynoms pol);
	polynoms search(std::string name);
	void clear(std::string name);
	size_t getsize();
	polynoms Arithmetic(std::string strexpr);
	int counttable = 0;
};