#pragma once
#include <stdexcept>
#include <algorithm>

template <class K, class T>
class UnorderedTable {
	std::pair<K, T>* mas;
	size_t size;
	size_t capacity;
	void resize() {
		capacity *= 2;
		std::pair<K, T>* mas2 = new std::pair<K, T>[capacity] {};
		std::copy(mas, mas + size, mas2);
		delete[] mas;
		mas = mas2;
	}
public:
	UnorderedTable() {
		size = 0;
		capacity = 10;
		mas = new std::pair<K, T>[capacity] {};
	}
	~UnorderedTable() {
		delete[] mas;
		mas = nullptr;
	}
	void add(const K& key, const T& data) {
		for (size_t i = 0; i < size; i++)
			if (mas[i].first == key) throw std::invalid_argument("In this table already exist element with this key");
		if (size == capacity) resize();
		mas[size++] = std::pair<K, T>{ key,data };
	}
	T find(const K& key) const {
		for (size_t i = 0; i < size; i++)
			if (mas[i].first == key) return mas[i].second;
		throw std::invalid_argument("There are no such key in this table");
	}
	void del(const K& key) {
		size_t i;
		for (i = 0; i < size; i++)
			if (mas[i].first == key) {
				size--;
				break;
			}
		for (i; i < size; i++)
			mas[i] = mas[i + 1];
	}
};