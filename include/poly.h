#pragma once
#include "list.h"

inline int comp(int d1, int d2);

class polynoms {
	list<std::pair<int, double>> monoms; //deg and koef
public:


	polynoms sort(list<std::pair<int, double>>& ent);
	polynoms();
	polynoms(list<std::pair<int, double>> ent);

	polynoms(const polynoms& pol);
	polynoms operator+(const double num);
	polynoms operator+(const polynoms& sec);
	polynoms& operator=(const polynoms& pol);

	polynoms operator*(const double& alpf) const;
	polynoms operator-(const polynoms& sec);
	std::pair<int, double> getmonom(int pos) const;
	int getsize() const;

	polynoms operator*(const polynoms& sec);

	bool operator==(const polynoms& sec) const;
	friend std::ostream& operator<<(std::ostream& os, const polynoms& p);
};