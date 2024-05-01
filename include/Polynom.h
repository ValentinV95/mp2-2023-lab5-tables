#pragma once
#include "List.h"


class Polynom : private List<std::pair<double, int>> {
	using List<std::pair<double, int>>:: head;

	std::string Error_string(const std::string& s, int i) const; //the method creates a string showing the error (highlights the specified element)

	std::string number_check(const std::string& s, int& i) const; //checks the number for correctness

	double valid(const std::string& s) const; //turns a string with a valid number into a number

	int count_deg(const std::string& s, int& i) const; //count degree of monom

public:
	Polynom();

	Polynom(const Polynom& p);

	Polynom(const std::string& str); //turns string into a polynom and check it fo correctness

	Polynom(const double& a);

	Polynom operator+ (const Polynom& p) const;
	
	Polynom operator+ (const double& a) const;

	Polynom operator*(const Polynom& p) const;

	Polynom operator* (const double& a) const;

	Polynom operator- (const Polynom& p) const;

	Polynom operator- (const double& a) const;

	bool operator==(const Polynom& p) const noexcept;

	bool operator!=(const Polynom& p) const noexcept;

	//using List<std::pair<double, int>>::operator!=;
	//using List<std::pair<double, int>>::operator==;

	using List<std::pair<double, int>>::operator=;

	double Pol_to_double() const;

	friend std::ostream& operator<<(std::ostream& ostr, const Polynom& p);

	friend std::istream& operator>>(std::istream& istr, Polynom& p);
};
