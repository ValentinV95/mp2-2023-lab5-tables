// ordered_table.h contains template class for an ordered table

#ifndef ODRERED_TABLE_H
#define ORDERED_TABLE_H

#include <algorithm>
#include "table_rec.h"

template<class T>
class ordered_table
{
public:
	ordered_table() : data(new TableRec<T>[128]), sz(0), cap(128) {}
	ordered_table(const ordered_table& ot) : data(new TableRec<T>[ot.cap]), 
											 sz(ot.sz), 
											 cap(ot.cap) 
	{ std::copy(ot.data, ot.data + sz, data); }

	~ordered_table()
	{
		delete[] data;
		data = nullptr;
		sz = 0;
		cap = 0;
	}

	ordered_table& operator=(const ordered_table& ot)
	{
		if (this == &ot)
			return *this;
		ordered_table tmp(ot);
		swap(*this, tmp);
		return *this;
	}

	T* find(const std::string& key)
	{
		size_t pos = _find_pos(key);
		if (data[pos].key == key)
			return &(data[pos].val);
		return nullptr;
	}

	void insert(const std::string& key, const T& t)
	{
		size_t pos = _find_pos(key);
		if (data[pos].key == key)
			return;

		if (sz == cap)
			resize();

		for (size_t i = sz; i > pos; i--)
			std::swap(data[i], data[i - 1]);

		data[pos] = TableRec<T>(key, t);
		sz++;
	}

	void insert(TableRec<T>&& tr) { insert(tr.key, tr.val); }

	void remove(const std::string& key)
	{
		size_t pos = _find_pos(key);
		if (data[pos].key != key)
			return;

		for (size_t i = pos; i < sz - 1; i++)
			std::swap(data[i], data[i + 1]);

		sz--;
	}

	size_t size() { return sz; }
	bool empty() { return sz == 0; }

	friend void swap(ordered_table& lhs, ordered_table& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.cap, rhs.cap);
	}

private:
	TableRec<T>* data;
	size_t sz, cap;

	size_t _find_pos(const std::string& key)
	{
		if (sz == 0)
			return 0;

		size_t l = 0;
		size_t r = sz;
		size_t pos;

		while (l != r)
		{
			pos = l + (r - l) / 2;
			if (data[pos].key < key)
				l = pos + 1;
			else
				r = pos;
		}

		pos = l + (r - l) / 2;
		return pos;
	}

	void resize()
	{
		TableRec<T>* tmp = new TableRec<T>[cap * 2];
		std::copy(data, data + cap, tmp);
		delete[] data;
		data = tmp;
		cap *= 2;
	}
};

#endif