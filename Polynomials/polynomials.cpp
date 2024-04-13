#include "polynomials.h"

Polynomial::Monome::Monome(double alp, int pow, Monome* next) : alpha(alp), m(pow)
{
	this->next = next;
}

Polynomial::Monome::Monome(const Monome& mn) : alpha(mn.alpha), m(mn.m)
{
	next = nullptr;
}

Polynomial::Monome::~Monome()
{
	m = 0;
	alpha = 0;
	next = nullptr;
}

Polynomial::Polynomial(int quan, double* arr) : quanity(0)
{
	head = new Monome(0, 0, nullptr); //фиктивная голова
	for (int i = 0; i+3 < quan; i+=4)
	{
		if (arr[i] != 0 && (arr[i+1] >= 0 && arr[i + 1] <= 9) &&
			(arr[i + 2] >= 0 && arr[i + 2] <= 9) &&
			(arr[i + 3] >= 0 && arr[i + 3] <= 9))
		{
			pop(arr[i], arr[i + 1]*100 + arr[i + 2]*10 + arr[i + 3]);
		}
		else if (arr[i] == 0)	continue;
		else
		{
			string except("Invalid input of monome ");
			except += to_string(i);
			throw invalid_argument(except);
		}

	}
}

Polynomial::Polynomial() : quanity(0)
{
	head = new Monome(0, 0, nullptr); //фиктивная голова
}

Polynomial::Polynomial(const Polynomial& p) : quanity(p.quanity)
{
	Monome* ind_p = p.head->next;
	head = new Monome(0, 0, nullptr); //фиктивная голова
	Monome* ind_this = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_this->next = new Monome(*ind_p);
		ind_p = ind_p->next;
		ind_this = ind_this->next;
	}
}
void Polynomial::pop(double alpha, int pow)
{
	if (quanity == 0)
	{
		head->next = new Monome(alpha, pow, nullptr);
		quanity++;
		return;
	}
	Monome* last = head->next;
	Monome* pre_last = head;
	int i;
	for (i = 0; i < quanity; i++)
	{
		if (pow > last->m)
		{
			pre_last->next = new Monome(alpha, pow, last);
			quanity++;
			return;
		}
		else if (last->m == pow)
		{
			last->alpha += alpha;
			if (abs(last->alpha) <1e-15)
			{
				quanity--;
				pre_last->next = last->next;
				delete last;
			}
			return;
		}
		pre_last = last;
		last = last->next;
	}
	if (i == quanity)
	{
		pre_last->next = new Monome(alpha, pow, nullptr);
		quanity++;
	}
}

bool Polynomial:: operator==(const Polynomial& p)
{
	Monome* ind_this = head->next;
	Monome* ind_p = p.head->next;
	if (quanity != p.quanity) return false;
	for (int i = 0; i < quanity; i++)
	{
		if (ind_this->m != ind_p->m ||
			ind_this->alpha != ind_p->alpha)
			return false;
		ind_this = ind_this->next;
		ind_p = ind_p->next;
	}
	return true;
}

bool Polynomial:: operator!=(const Polynomial& p)
{
	return !(operator==(p));
}


Polynomial& Polynomial:: operator=(const Polynomial& p)
{
	if (this == &p)
		return *this;

	Monome* ind = head, * ind_next = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_next = ind_next->next;
		delete ind;
		ind = ind_next;
	}

	quanity = p.quanity;
	Monome* ind_p = p.head->next;
	head = new Monome(0, 0, nullptr); //фиктивная голова [самокритика]
	Monome* ind_this = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_this->next = new Monome(*ind_p);
		ind_p = ind_p->next;
		ind_this = ind_this->next;
	}
	return *this;
}

Polynomial& Polynomial:: operator *=(double factor)
{
	if (factor == 0)
	{
		Monome* ind = head, * ind_next = head;
		for (int i = 0; i < quanity; i++)
		{
			ind_next = ind_next->next;
			delete ind;
			ind = ind_next;
		}
		quanity = 0;
		return *this;
	}
	Monome* prev = head->next;
	for (int i = 0; i < quanity; i++)
	{
		prev->alpha *= factor;
		prev = prev->next;
	}
	return *this;
}

Polynomial Polynomial:: operator *(double factor)
{
	Polynomial tmp(*this);
	return tmp.operator*=(factor);
}

Polynomial& Polynomial:: operator +=(const Polynomial& p)
{
	Monome* ind_p = p.head->next, * this_last = head->next, * this_pre_last = head;
	for (int i = 0; i < p.quanity; i++)
	{
		while (this_last != nullptr && ind_p->m < this_last->m)
		{
			this_pre_last = this_last;
			this_last = this_last->next;
		}
		if (this_last == nullptr || ind_p->m > this_last->m)
		{
			this_pre_last = this_pre_last->next = new Monome(*ind_p);
			this_pre_last->next = this_last;
			quanity++;
		}
		else if (ind_p->m == this_last->m)
		{
			this_last->alpha += ind_p->alpha;
			if (abs(this_last->alpha) < 1e-15)
			{
				quanity--;
				this_pre_last->next = this_last->next;
				delete this_last;
				this_last = this_pre_last->next;
			}
		}
		ind_p = ind_p->next;
	}
	return *this;
}

Polynomial Polynomial:: operator +(const Polynomial& p)
{
	Polynomial tmp(*this);
	return tmp.operator+=(p);
}

Polynomial Polynomial::operator -(const Polynomial& p)
{
	Polynomial tmp(*this);
	return tmp.operator-=(p);
}

Polynomial& Polynomial:: operator -=(const Polynomial& p)
{
	Polynomial tmp(p);
	tmp*=(-1);
	return operator+=(tmp);
}

Polynomial Polynomial:: operator *(const Polynomial& p)
{
	Polynomial tmp;
	Monome* ind_this = head->next;
	for (int i = 0; i < quanity; i++)
	{
		Monome* ind_p = p.head->next;
		for (int j = 0; j < p.quanity; j++)
		{
			if (((ind_this->m % 10 + ind_p->m % 10) < 10) &&
				(((ind_this->m / 10) % 10 + (ind_p->m / 10) % 10) < 10) &&
				((ind_this->m / 100 + ind_p->m / 100) < 10))

				tmp.pop(ind_this->alpha * ind_p->alpha, ind_this->m + ind_p->m);

			else throw invalid_argument("The pow of the result is above 9");
			ind_p = ind_p->next;
		}
		ind_this = ind_this->next;
	}
	return tmp;
}

Polynomial& Polynomial:: operator *=(const Polynomial& p)
{
	Polynomial tmp = *this * p;
	*this = tmp;
	return *this;
}

Polynomial::~Polynomial()
{
	Monome* ind = head, * ind_next = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_next = ind_next->next;
		delete ind;
		ind = ind_next;
	}
	quanity = 0;
	head = nullptr;
}

int Polynomial:: poly_out(double* tmp)
{
	Monome* last = head->next;
	for (int i = 0; i < quanity; i++)
	{
		tmp[4 * i] = last->alpha;
		tmp[4 * i + 1] = last->m / 100;
		tmp[4 * i + 2] = (last->m / 10) % 10;
		tmp[4 * i + 3] = last->m % 10;
		last = last->next;
	}
	return quanity;
}