#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <stack>
#include "polynoms.h"
#include "error.h"

Polynom::Monom::Monom(unsigned int d, double c) : coef(c), deg(d)
{
	if (deg >= MAX_MONOM_DEGREE * MAX_MONOM_DEGREE * MAX_MONOM_DEGREE)
	{
		std::stringstream ss;
		ss << "Monom compressed degree is greater than " << MAX_MONOM_DEGREE;
		throw std::runtime_error(ss.str());
	}
}

Polynom::Monom::Monom(unsigned int x_d, unsigned int y_d, unsigned z_d, double c) : coef(c), deg(z_d +
																								MAX_MONOM_DEGREE * y_d + 
																								MAX_MONOM_DEGREE * MAX_MONOM_DEGREE * x_d)
{
	if (x_d > MAX_MONOM_DEGREE - 1)
	{
		std::stringstream ss;
		ss << "Monom x degree is greater than " << MAX_MONOM_DEGREE - 1;
		throw std::runtime_error(ss.str());
	}

	else if (y_d > MAX_MONOM_DEGREE - 1)
	{
		std::stringstream ss;
		ss << "Monom y degree is greater than " << MAX_MONOM_DEGREE - 1;
		throw std::runtime_error(ss.str());
	}

	else if (z_d > MAX_MONOM_DEGREE - 1)
	{
		std::stringstream ss;
		ss << "Monom z degree is greater than " << MAX_MONOM_DEGREE - 1;
		throw std::runtime_error(ss.str());
	}
}

Polynom::Monom Polynom::Monom::operator*(const Monom& m)
{
	unsigned int x_d1 = deg / (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE);
	unsigned int y_d1 = (deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d1) / MAX_MONOM_DEGREE;
	unsigned int z_d1 = deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d1 - MAX_MONOM_DEGREE * y_d1;

	unsigned int x_d2 = m.deg / (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE);
	unsigned int y_d2 = (m.deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d2) / MAX_MONOM_DEGREE;
	unsigned int z_d2 = m.deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d2 - MAX_MONOM_DEGREE * y_d2;
	return Monom(x_d1+x_d2, y_d1+y_d2, z_d1+z_d2, coef*m.coef);
}

bool Polynom::Monom::operator==(const Monom& m) const noexcept { return (deg == m.deg) && (std::abs(coef - m.coef) < EPS); }
bool Polynom::Monom::operator!=(const Monom& m) const noexcept { return !(*this == m); }

bool Polynom::Monom::operator<(const Monom& m) const noexcept
{
	unsigned int x_d1 = deg / (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE);
	unsigned int y_d1 = (deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d1) / MAX_MONOM_DEGREE;
	unsigned int z_d1 = deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d1 - MAX_MONOM_DEGREE * y_d1;

	unsigned int x_d2 = m.deg / (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE);
	unsigned int y_d2 = (m.deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d2) / MAX_MONOM_DEGREE;
	unsigned int z_d2 = m.deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d2 - MAX_MONOM_DEGREE * y_d2;

	unsigned int deg_full = x_d1 + y_d1 + z_d1;
	unsigned int mdeg_full = x_d2 + y_d2 + z_d2;

	if (deg_full < mdeg_full) return true;
	else if (deg_full == mdeg_full) return deg < m.deg;
	return false;
}

Polynom::Polynom() {}

Polynom::Polynom(const std::string& s) { fill(s); }

Polynom::Polynom(const Polynom& p) : polynom(p.polynom) {}
Polynom::Polynom(Polynom&& p) noexcept : polynom(std::move(p.polynom)) {}

Polynom& Polynom::operator=(const Polynom& p)
{
	if (this == &p)
		return *this;
	Polynom tmp(p);
	swap(*this, tmp);
	return *this;
}

Polynom& Polynom::operator=(Polynom&& p) noexcept
{
	if (this == &p)
		return *this;
	Polynom tmp(std::move(p));
	swap(*this, tmp);
	return *this;
}

Polynom Polynom::operator+(const Polynom& p)
{
	Polynom tmp;
	auto it1 = polynom.begin();
	auto it2 = p.polynom.begin();

	for (; it1 != polynom.end() && it2 != polynom.end(); )
	{
		if (*it1 < *it2)
		{
			tmp.polynom.insert(*it2);
			++it2;
		}

		else if (it1->deg == it2->deg)
		{
			if (std::abs(it1->coef + it2->coef) < EPS);
			else tmp.polynom.insert(Monom(it1->deg, it1->coef + it2->coef));
			++it1;
			++it2;
		}

		else
		{
			tmp.polynom.insert(*it1);
			++it1;
		}
	}

	for (; it1 != polynom.end(); ++it1) tmp.polynom.insert(*it1);
	for (; it2 != p.polynom.end(); ++it2) tmp.polynom.insert(*it2);
	tmp.polynom = tmp.polynom.reversed();

	return tmp;
}

Polynom Polynom::operator-(const Polynom& p)
{
	return Polynom(*this + (p * -1.0));
}

Polynom Polynom::operator*(const Polynom& p)
{
	Polynom res;

	for (auto& it : p.polynom)
	{
		Polynom tmp(*this);
		for (auto& m : tmp.polynom)
			m = m * it;
		res = res + tmp;
	}

	return res;
}

Polynom Polynom::operator*(double d) const
{
	Polynom tmp;
	for (auto& it : polynom)
		if(std::abs(it.coef * d) >= EPS) tmp.polynom.insert(Monom(it.deg, it.coef * d));

	tmp.polynom = tmp.polynom.reversed();
	return tmp;
}

bool Polynom::operator==(const Polynom& p) const noexcept { return polynom == p.polynom; }
bool Polynom::operator!=(const Polynom& p) const noexcept { return polynom != p.polynom; }

void swap(Polynom& lhs, Polynom& rhs) noexcept { swap(lhs.polynom, rhs.polynom); }

std::string Polynom::getString() const
{
	if (polynom.isEmpty()) return "0";

	std::stringstream ss;
	for(auto it = polynom.begin(); it != polynom.end(); )
	{
		unsigned int x_d = it->deg / (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE);
		unsigned int y_d = (it->deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d) / MAX_MONOM_DEGREE;
		unsigned int z_d = it->deg - (MAX_MONOM_DEGREE * MAX_MONOM_DEGREE) * x_d - MAX_MONOM_DEGREE * y_d;

		if (std::abs(it->coef - 1.0) < EPS && it->deg != 0);
		else if (std::abs(it->coef + 1.0) < EPS && it->deg != 0) ss << "-";
		else ss << it->coef;

		if(x_d > 0)
			x_d > 1 ? (ss << "x^" << x_d) : (ss << "x");
		if(y_d > 0)
			y_d > 1 ? (ss << "y^" << y_d) : (ss << "y");
		if(z_d > 0)
			z_d > 1 ? (ss << "z^" << z_d) : (ss << "z");

		++it;
		if (it != polynom.end() && it->coef > 0.0) ss << "+";
	}

	return ss.str();
}

void Polynom::insertMonom(const Monom& m)
{
	if (std::abs(m.coef) < EPS) return;
	auto it = polynom.begin();
	auto prev = polynom.before_begin();

	for (; it != polynom.end() && m < *it; ++it, ++prev);
	if (it != polynom.end())
	{
		if (m.deg == it->deg)
		{
			if (std::abs(m.coef + it->coef) >= EPS)
				it->coef += m.coef;
			else
				polynom.eraseAfter(prev);
		}

		else polynom.insertAfter(prev, m);
	}

	else polynom.insertAfter(prev, m);
}

void Polynom::insertMonom(unsigned int x_d, unsigned int y_d, unsigned z_d, double c) { insertMonom(Monom(x_d, y_d, z_d, c)); }

std::ostream& operator<<(std::ostream& os, const Polynom& p) { return os << p.getString(); }
std::istream& operator>>(std::istream& is, Polynom& p)
{
	std::string s;
	std::getline(std::cin, s);
	p.fill(s);
	return is;
}

void Polynom::fill(const std::string& s)
{
	if (s.size() == 0) throw std::runtime_error("An empty string was given");
	if (*s.begin() == '+') throw_error(s, "Unexpected token", 0);
	if (s.back() == '+' || s.back() == '-') throw_error(s, "Unexpected token", s.size()-1);

	Polynom tmp;
	aux::PolynomReadState prs = aux::INIT;
	double coef = 0.0;
	double sign = 1.0;
	unsigned int x_deg = 0;
	unsigned int y_deg = 0;
	unsigned int z_deg = 0;

	for (size_t i = 0; i < s.size(); )
	{
		switch (prs)
		{
		case aux::INIT:
			if (isWhitespace(s[i])) i++;
			else if (s[i] == '+') 
			{ 
				if (s[i + 1] == '+' || s[i + 1] == '-') throw_error(s, "Unexpected character", i);
				sign = 1.0;
				i++; 
			}

			else if (s[i] == '-')
			{ 
				if (s[i + 1] == '+' || s[i + 1] == '-') throw_error(s, "Unexpected character", i);
				sign = -1.0;
				i++;
			}

			else if (s[i] == '.' || (s[i] >= '0' && s[i] <= '9')) { prs = aux::COEF; }
			else if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z') { coef = 1.0; prs = aux::MONOM; }
			else throw_error(s, "Unexpected character", i);

			continue;

		case aux::COEF:
			coef = aux::tokenizeDouble(i, s);
			if (s[i] == '+' || s[i] == '-' || s[i] == '\0')
			{
				tmp.insertMonom(x_deg, y_deg, z_deg, sign*coef); coef = 0.0; x_deg = y_deg = z_deg = 0; sign = 1.0;
				prs = aux::INIT;
			}

			else if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z')
			{
				prs = aux::MONOM;
			}

			else throw_error(s, "Unexpected token", i);
			continue;

		case aux::MONOM:
			for (; i < s.size() && !isWhitespace(s[i]) && s[i] != '+' && s[i] != '-';)
			{
				switch (s[i])
				{
				case 'x':
					if (s[++i] == '^') x_deg += aux::tokenizeInt(++i, s);
					else x_deg += 1;
					break;

				case 'y':
					if (s[++i] == '^') y_deg += aux::tokenizeInt(++i, s);
					else y_deg += 1;
					break;

				case 'z':
					if (s[++i] == '^') z_deg += aux::tokenizeInt(++i, s);
					else z_deg += 1;
					break;

				default:
					throw_error(s, "Unexpected character", i);
					break;
				}
			}

			tmp.insertMonom(x_deg, y_deg, z_deg, sign*coef); coef = 0.0; x_deg = y_deg = z_deg = 0; sign = 1.0;
			prs = aux::INIT;
			continue;
		}
	}

	swap(*this, tmp);
}

double aux::tokenizeDouble(size_t& i, const std::string& s)
{
	DoubleTokenizerState ntst = NT_INIT;
	std::stack<char> beforePointChars;
	std::stack<char> afterPointChars;
	std::stack<char> expChars;

	size_t first_char = i;
	size_t last_char = i;
	double val = 0.0;
	double pow = 1.0;
	double pow_frac = 0.1;
	double exp_sign = 1.0;
	double exp = 0.0;

	if (s[i] == '-') { i++; }

	for (; i < s.size();)
	{
		switch (ntst)
		{
		case NT_INIT:
			last_char = i;
			if (s[i] == '.') { i++; ntst = NUM2; }
			else if (s[i] >= '1' && s[i] <= '9') { ntst = NUM1; }
			else if (s[i] == '0') { ntst = ZERO_FIRST; }
			continue;

		case NUM1:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') beforePointChars.push(s[i++]);
			else if (s[i] == '.') { i++; ntst = NUM2; }
			else if (s[i] == 'e') { i++; ntst = EXP; }
			else break;
			continue;

		case NUM2:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') afterPointChars.push(s[i++]);
			else if (s[i] == 'e') { i++; ntst = EXP; }
			else break;
			continue;

		case NUM3:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') expChars.push(s[i++]);
			else if (s[i] == '.') { throw_error(s, "Invalid number format", last_char); }
			else break;
			continue;

		case EXP:
			last_char = i;
			if (s[i] == '+') i++;
			else if (s[i] == '-') { i++; exp_sign = -1.0; }
			else throw_error(s, "Invalid number format", last_char);

			if (s[i] >= '1' && s[i] <= '9') ntst = NUM3;
			else if (s[i] == '0' && s[i + 1] != '0') ntst = NUM3;
			else throw_error(s, "Invalid number format", (i < s.size() ? i : i - 1));
			continue;

		case ZERO_FIRST:
			last_char = i;
			if (s[++i] == '.') { i++; ntst = NUM2; }
			else break;
			continue;
		}

		break;
	}

	if (s[i - 1] == '.' && (i - first_char < 2)) throw_error(s, "Invalid number format", last_char);
	if (ntst != NUM1 && ntst != NUM2 && ntst != NUM3 && ntst != ZERO_FIRST)
		throw_error(s, "Invalid number format", last_char);

	while (!beforePointChars.empty())
	{
		val += pow * (beforePointChars.top() - '0');
		pow *= 10;
		beforePointChars.pop();
	}

	// перевод в double
	std::stack<char> tmp;
	while (!afterPointChars.empty())
	{
		tmp.push(afterPointChars.top());
		afterPointChars.pop();
	}

	while (!tmp.empty())
	{
		val += pow_frac * (tmp.top() - '0');
		pow_frac *= 0.1;
		tmp.pop();
	}

	pow = 1;
	while (!expChars.empty())
	{
		exp += pow * (expChars.top() - '0');
		pow *= 10;
		expChars.pop();
	}

	return val * std::pow(10, exp_sign * exp);
}

unsigned int aux::tokenizeInt(size_t& i, const std::string& s)
{
	std::stack<char> chars;

	size_t first_char = i;
	size_t last_char = i;
	unsigned int val = 0.0;

	if (s[i] >= '1' && s[i] <= '9') chars.push(s[i++]);
	else throw_error(s, "Unexpected character", i);

	for (; i < s.size() && s[i] != '+' && s[i] != '-' && s[i] != 'x' && s[i] != 'y' && s[i] != 'z'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9') chars.push(s[i]);
		else throw_error(s, "Unexpected character", i);
	}

	std::stack<char> tmp;
	while (!chars.empty())
	{
		tmp.push(chars.top());
		chars.pop();
	}

	unsigned long pow = std::powl(10, tmp.size() - 1);
	while (!tmp.empty())
	{
		val += pow * (tmp.top() - '0');
		pow /= 10;
		tmp.pop();
	}

	return val;
}