#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

template< typename U, typename V>
class Hash
{
private:
	class List
	{
	private:
		class Node
		{
		public:
			V* data;
			U* key;
			Node* next;
			Node(const U& ky, const V& d)
			{
				key = new U(ky);
				data = new V(d);
				next = nullptr;
			}

			Node() : key(nullptr), data(nullptr), next(nullptr) {}

			~Node()
			{
				delete data;
				delete key;
				next = nullptr;
			}
		};
		Node* head;
	public:
		List()
		{
			head = nullptr;
		}
		void push_head(const U& key, const V& elem)
		{
			Node* tmp = new Node(key, elem);
			tmp->next = head;
			head = tmp;
		}

		bool avail(const U& ky)
		{
			Node* cur = head;
			while (cur != nullptr && *(cur->key) != ky)
				cur = cur->next;
			if (cur!=nullptr && *(cur->key) == ky)
				return true;
			else
				return false;
		}

		V& find(const U& ky)
		{
			Node* cur = head;
			while (cur != nullptr && *(cur->key) != ky)
				cur = cur->next;
			if (cur != nullptr && *(cur->key) == ky)
				return *(cur->data);
			else
				throw invalid_argument("There is no element with such key");
		}
		void del(const U& ky)
		{
			Node* cur = head, * prev = head;
			if (head == nullptr) return;
			if (*(head->key) == ky)
			{
				head = head->next;
				delete cur;
				return;
			}
			while (cur != nullptr && *(cur->key) != ky)
			{
				prev = cur;
				cur = cur->next;
			}
			if (cur != nullptr && *(cur->key) == ky)
			{
				prev->next = cur->next;
				delete cur;
			}
		}
		~List()
		{
			Node* ind = head, * ind_next = head;
			while (ind != nullptr)
			{
				ind_next = ind_next->next;
				delete ind;
				ind = ind_next;
			}
			head = nullptr;
		}
	};
	List* data;
	size_t n;
public:
	Hash(size_t size = 50): n(size)
	{
		data = new List[n]();
	}

	size_t hsh(const U& key)
	{
		size_t res = 0;
		for (size_t i = 0; i < key.length(); i++)
		{
			res += abs(key[i]) * pow(7, i);
			res = res % n;
		}
		return res;
	}
	void push(const U& key, const V& value)
	{
		data[hsh(key)].push_head(key, value);
	}
	void del(const U& key)
	{
		data[hsh(key)].del(key);
	}
	bool avail(const U& key)
	{
		return data[hsh(key)].avail(key);
	}
	V& find(const U& key)
	{
		return data[hsh(key)].find(key);
	}
};