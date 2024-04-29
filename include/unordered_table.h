// unordered_table.h contains template class for an unordered table

#ifndef UNORDERED_TABLE_H
#define UNORDERED_TABLE_H

#include <algorithm>
#include "table_rec.h"

template<class T>
class unordered_table
{
public:
	unordered_table() : data(new TableRec<T>[128]), sz(0), cap(128) {}
	unordered_table(const unordered_table& ut) : data(new TableRec<T>[ut.cap]),
												 sz(ut.sz), cap(ut.cap)
	{ std::copy(ut.data, ut.data + sz, data); }

	~unordered_table()
	{
		delete[] data;
		data = nullptr;
		sz = 0;
		cap = 0;
	}

	unordered_table& operator=(const unordered_table& ut)
	{
		if (this == &ut)
			return *this;
		unordered_table tmp(ut);
		swap(*this, tmp);
		return *this;
	}

	T* find(const std::string& key)
	{
		for (size_t i = 0; i < sz; ++i)
			if (data[i].key == key)
				return &(data[i].val);

		return nullptr;
	}

	void insert(const std::string& key, const T& t)
	{
		for (size_t i = 0; i < sz; ++i)
			if (data[i].key == key)
				return;

		if (sz == cap)
			resize();
		data[sz++] = TableRec<T>(key, t);
	}

	void insert(TableRec<T>&& tr) { insert(tr.key, tr.val); }

	void remove(const std::string& key)
	{
		for (size_t i = 0; i < sz; ++i)
			if (data[i].key == key)
			{
				data[i] = data[--sz];
				return;
			}
	}

	size_t size() { return sz; }
	bool empty() { return sz == 0; }

	friend void swap(unordered_table& lhs, unordered_table& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.cap, rhs.cap);
	}

private:
	TableRec<T>* data;
	size_t sz, cap;

	void resize()
	{
		TableRec<T>* tmp = new TableRec<T>[cap * 2];
		std::copy(data, data + cap, tmp);
		delete[] data;
		data = tmp;
		cap *= 2;
	}
};

#endif // !UNORDERED_TABLE_H
