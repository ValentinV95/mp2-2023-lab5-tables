#pragma once
#include <cstdlib>
#include <iostream>
#include <exception>
using namespace std;

//typedef string L;

template<typename L, typename R>
class LR_UnordTable
{
private:
	class LR_pair
	{
	public:
		L* l_data;
		R* r_data;
		LR_pair()
		{
			l_data = nullptr;
			r_data = nullptr;
		}
		LR_pair(const L& l_d, const R& r_d)
		{
			l_data = new L(l_d);
			r_data = new R(r_d);
		}
		LR_pair& operator = (const LR_pair& pair) //??
		{
			if (this == &pair)
				return *this;

			delete l_data;
			delete r_data;

			l_data = new L(*pair.l_data);
			r_data = new R(*pair.r_data);
			return *this;
		}
		~LR_pair()
		{
			delete l_data;
			delete r_data;
		}
	};
	LR_pair* data;
	size_t capasity, size;
	void resize()
	{
		LR_pair* tmp = new LR_pair[capasity *= 2]();
		std::copy(data + 0, data + size, tmp);
		delete[]data;
		data = tmp;
	}
public:
	LR_UnordTable(size_t cap = 10) : capasity(cap), size(0)
	{
		data = new LR_pair[capasity]();
	}
	void push(const LR_pair& pair)
	{
		if (size == capasity)
			resize();
		data[size++] = pair;
	}
	void del_by_Ldata(const L& name)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (*data[i].l_data == name)
			{
				delete data[i].l_data;
				delete data[i].r_data;
				size--;
				for (size_t j = i; j < size; j++)
				{
					data[j] = data[j + 1];
				}
			}
		}
	}
	void del_by_Rdata(const R& name)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (*data[i].r_data == name)
			{
				delete data[i].l_data;
				delete data[i].r_data;
				size--;
				for (size_t j = i; j < size; j++)
				{
					data[j] = data[j + 1];
				}
			}
		}
	}
	void push(const L& l_d, const R& r_d)
	{
		if (size == capasity)
			resize();
		data[size].l_data = new L(l_d);
		data[size++].r_data = new R(r_d);
	}
	R& return_by_Ldata(const L& name)	//returns r_data with l_data == name or NULL
	{
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (*data[i].l_data == name)
			{
				return *data[i].r_data;
			}
		}
		if (i == size)
		{
			throw invalid_argument("There is no element with l_data == name");
		}
	}
	L& return_by_Rdata(const R& name)	//returns l_data with r_data == name or NULL
	{
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (*data[i].r_data == name)
			{
				return *data[i].l_data;
			}
		}
		if (i == size)
		{
			throw invalid_argument("There is no element with r_data == name");
		}
	}
	bool is_Rdata(const R& name)	//returns true if there is r_data == name; otherwise returns false
	{
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (*data[i].r_data == name)
			{
				return true;
			}
		}
		if (i == size) return false;
	}
	bool is_Ldata(L name)	//returns true if there is l_data == name; otherwise returns false
	{
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (*data[i].l_data == name)
			{
				return true;
			}
		}
		if (i == size) return false;
	}
};
