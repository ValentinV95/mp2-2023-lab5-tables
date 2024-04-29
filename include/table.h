// table.h contains template class for a table with user-defined container
// container must be a template class

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <chrono>
#include "table_rec.h"

template<class T>
class unordered_table;

template<class T,
		 template<class> class Container = unordered_table>
class Table
{
public:
	Table() {}
	Table(const Table& t) : ct(t.ct) {}

	Table& operator=(const Table& t)
	{
		if (this == &t)
			return *this;
		ct = t.ct;
		return *this;
	}

	T* find(const std::string& key)
	{
		std::cout << "Performing search in " << typeid(Container).name() << std::endl;
		const auto start{ std::chrono::steady_clock::now() };
		T* p = ct.find(key);
		const auto end{ std::chrono::steady_clock::now() };
		const std::chrono::duration<double> elapsed{ end - start };
		std::cout << "Operation done, took " << elapsed.count() << " ms" << std::endl;
		return p;
	}

	void insert(const std::string& key, const T& t)
	{
		std::cout << "Performing insertion in " << typeid(Container).name() << std::endl;
		const auto start{ std::chrono::steady_clock::now() };
		ct.insert(TableRec<T>(key, t));
		const auto end{ std::chrono::steady_clock::now() };
		const std::chrono::duration<double> elapsed{ end - start };
		std::cout << "Operation done, took " << elapsed.count() << " ms" << std::endl;
	}

	void insert(TableRec<T>&& tr) { insert(tr.key, tr.val); }

	void remove(const std::string& key)
	{
		std::cout << "Performing remove in " << typeid(Container).name() << std::endl;
		const auto start{ std::chrono::steady_clock::now() };
		ct.remove(key);
		const auto end{ std::chrono::steady_clock::now() };
		const std::chrono::duration<double> elapsed{ end - start };
		std::cout << "Operation done, took " << elapsed.count() << " ms" << std::endl;
	}

	size_t size() { return ct.size(); }
	bool empty() { return ct.empty(); }

private:
	Container<T> ct;
};

#endif // !TABLE_H
