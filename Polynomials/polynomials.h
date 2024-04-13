#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Polynomial
{
private:
	class Monome
	{
	public:
		double alpha;
		int m;
		Monome* next;
		Monome(double alp, int pow, Monome* next);
		Monome(const Monome& mn);//конструктор копирования мономов. Следующий моном - null
		~Monome();
	};
	Monome* head;
	int quanity;
public:
	Polynomial(int quan, double* arr); //конструктор полинома из массива гарантированно верных данных (для тестов)
	Polynomial(const Polynomial& p);  //к-р копирования (не плодит указатели на один и тот же объект, next = nullptr)
	Polynomial();
	~Polynomial();
	void pop(double alpha, int pow);
	bool operator==(const Polynomial& p);
	bool operator!=(const Polynomial& p);
	Polynomial& operator=(const Polynomial& p);
	Polynomial operator *(double factor);
	Polynomial& operator *=(double factor);
	Polynomial operator +(const Polynomial& p);
	Polynomial& operator +=(const Polynomial& p);
	Polynomial operator -(const Polynomial& p);
	Polynomial& operator -=(const Polynomial& p);
	Polynomial operator *(const Polynomial& p);
	Polynomial& operator *=(const Polynomial& p);
	int poly_out(double* tmp);//возвращает кол-во мономов, в tmp записывает мономы (к-т, степень x, степень y, степень z)
	friend istream& operator>>(istream& istr, Polynomial& p)
	{
		Monome* ind = p.head, * ind_next = p.head;
		for (int i = 0; i < p.quanity; i++)
		{
			ind_next = ind_next->next;
			delete ind;
			ind = ind_next;
		}
		p.quanity = 0;

		p.head = new Monome(0, 0, nullptr); //фиктивная голова
		double a;
		int pow_x, pow_y, pow_z, quan;
		istr >> quan;
		for (int i = 0; i < quan; i++)
		{
			istr >> a >> pow_x >> pow_y >> pow_z;
			if (a != 0 && (pow_x >= 0 && pow_x <= 9) &&
				(pow_y >= 0 && pow_y <= 9) &&
				(pow_z >= 0 && pow_z <= 9))
			{
				p.pop(a, pow_x * 100 + pow_y * 10 + pow_z);
			}
			else if (a == 0)	continue;
			else
			{
				string except("Invalid input of monome ");
				except += to_string(i);
				throw invalid_argument(except);
			}

		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const Polynomial& p)
	{
		Monome* prev = p.head->next;
		if (p.quanity != 0)
		{
			ostr << prev->alpha << " x^" << (prev->m) / 100 << " y^" << ((prev->m) % 100) / 10 << " z^" << (prev->m) % 10;
			prev = prev->next;
		}
		else ostr << '0';
		for (int i = 1; i < p.quanity; i++)
		{
			ostr << " + " << prev->alpha << " x^" << (prev->m) / 100 << " y^" << ((prev->m) % 100) / 10 << " z^" << (prev->m) % 10;
			prev = prev->next;
		}
		return ostr;
	}
};