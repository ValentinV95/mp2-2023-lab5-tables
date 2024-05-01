// hash_table.h contains template class for a hash table with polynomial hash

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <algorithm>
#include <cmath>
#include "table_rec.h"
#include "list.h"

template<class T>
class hash_table
{
public:
	hash_table() : sz(0) {}
	hash_table(const hash_table& ht) = default;
	hash_table& operator=(const hash_table& ht) = default;

	T* find(const std::string& key)
	{
		size_t h = hash(key);
		auto it = data[h].begin();

		for (auto it = data[h].begin(); it != data[h].end() && it->key != key; ++it);

		if(it != nullptr)
			return &(it->val);
		return nullptr;
	}

	void insert(const std::string& key, const T& t)
	{
		if(find(key) == nullptr)
		{
			data[hash(key)].insert(TableRec<T>(key, t));
			sz++;
		}
	}

	void insert(TableRec<T>&& tr) { insert(tr.key, tr.val); }

	void remove(const std::string& key)
	{
		size_t h = hash(key);
		auto prev = data[h].before_begin();
		auto cur = data[h].begin();

		if (cur != nullptr)
		{
			while (cur->key != key)
			{
				++prev;
				++cur;
			}

			data[h].eraseAfter(prev);
			sz--;
		}
	}

	size_t size() { return sz; }
	bool empty() { return sz == 0; }

	friend void swap(hash_table& lhs, hash_table& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.sz, rhs.sz);
	}

private:
	List<TableRec<T>> data[128];
	size_t sz;

	size_t hash(const std::string& key)
	{
		size_t hash = 0;
		size_t shift = 1;

		for (size_t i = 0; i < key.length(); ++i)
		{
			hash += (unsigned char)key[i] * shift;
			shift = shift << 1;
		}

		return hash % 128;
	}
};

#endif