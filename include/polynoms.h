#ifndef POLYNOMS_H
#define POLYNOMS_H

#include <iostream>
#include <string>
#include "list.h"

#define MAX_MONOM_DEGREE 20
#define EPS 1e-7

// Реализация многочлена на упорядоченном односвязном списке. Степень многочлена ограничена константой MAX_MONOM_DEGREE
class Polynom
{
public:
	Polynom();
	Polynom(const std::string& s);
	Polynom(const Polynom& p);
	Polynom(Polynom&& p) noexcept;

	Polynom& operator=(const Polynom& p);
	Polynom& operator=(Polynom&& p) noexcept;
	
	Polynom operator+(const Polynom& p);
	Polynom operator-(const Polynom& p);
	Polynom operator*(const Polynom& p);
	Polynom operator*(double d) const;
	
	bool operator==(const Polynom& p) const noexcept;
	bool operator!=(const Polynom& p) const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
	friend std::istream& operator>>(std::istream& is, Polynom& p);

	friend void swap(Polynom& lhs, Polynom& rhs) noexcept;
	std::string getString() const;
	void insertMonom(unsigned int x_d, unsigned int y_d, unsigned z_d, double c = 0.0); // операция вставки монома в полином
	void fill(const std::string& s); // чтение полинома из строки

private:
	class Monom
	{
	public:
		Monom(unsigned int d = 0, double c = 0.0);
		Monom(unsigned int x_d, unsigned int y_d, unsigned z_d, double c = 0.0);

		Monom operator*(const Monom& m);

		bool operator==(const Monom& m) const noexcept;
		bool operator!=(const Monom& m) const noexcept;
		bool operator<(const Monom& m) const noexcept; // упорядочивание мономов по суммам степеней

		double coef; // коэффициент при мономе
		unsigned int deg; // свёрнутая степень монома
	};

	List<Monom> polynom;
	void insertMonom(const Monom& m); // операция вставки монома в полином
};

// Вспомогательные функции, используемые для считывания полинома из строки
namespace aux
{
	enum PolynomReadState
	{
		INIT,
		COEF,
		MONOM,
	};

	enum DoubleTokenizerState
	{
		NT_INIT,
		ZERO_FIRST, // первая цифра - ноль
		NUM1, // часть числа до точки
		NUM2, // часть числа после точки
		EXP, // обработка знака степени
		NUM3, // степень
	};

	double tokenizeDouble(size_t& i, const std::string& s);
	unsigned int tokenizeInt(size_t& i, const std::string& s);
}

#endif //POLYNOMS_H