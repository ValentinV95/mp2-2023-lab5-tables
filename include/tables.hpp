#pragma once
#include <stdexcept>
#include <vector>
#include "avltree.hpp"
#include "informer.hpp"

// Unordered table, ordered table (AVL Tree), hash table (hash chain technique)

enum State {
	kNULL, kCONTENT, kDELETED
};

template <typename T>
size_t hasha(const T& data, Informer& inf) {
	inf.op();
	return static_cast<size_t>(data);
}

template <>
size_t hasha<std::string>(const std::string& data, Informer& inf) {
	const size_t pownum = 3;
	size_t res = 0;
	for (size_t i = 0; i < data.size(); i++) {
		inf.op(2);
		res += (static_cast<int>(data[i]) + 127) * static_cast<size_t>(std::pow(pownum, i));
	}
	return res;
}

template <typename KeyType, typename ValueType>
class HashTable {
public:
	HashTable(size_t capacity, std::ostream& stream = std::cout) : inf_(Table::kHash, stream), data_(capacity), capacity_(capacity) {}
	ValueType* find(const KeyType& key) {
		size_t index = find_index(key);
		inf_.inform(TableOps::kFind);
		return &data_[index].value_;
	}
	void insert(const KeyType& key, const ValueType& value) {
		size_t i = 0;
		size_t h = hasha<KeyType>(key, inf_);
		while (!data_[(h + i) % capacity_].isEmpty()) {
			inf_.op(3);
			i++;
			if (i >= capacity_) {
				throw std::runtime_error("Too much lines in hash table");
			}
		}
		inf_.op(3);
		data_[(h + i) % capacity_].key_ = key;
		data_[(h + i) % capacity_].value_ = value;
		data_[(h + i) % capacity_].state_ = kCONTENT;
		inf_.inform(TableOps::kPush);
	}
	void pop(const KeyType& key) {
		int x = find_index(key);
		inf_.op();
		if (x == -1) {
			inf_.inform(TableOps::kPop);
			throw std::invalid_argument("Table doesn't have this key");
		}
		inf_.op();
		data_[x].state_ = kDELETED;
		inf_.inform(TableOps::kPop);
	}
private:
	struct ValueWithState {
	public:
		KeyType key_;
		ValueType value_;
		State state_;
		bool isEmpty() {
			return (state_ == kNULL || state_ == kDELETED);
		}
		bool isNull() {
			return (state_ == kNULL);
		}
	};
	int find_index(const KeyType& key) {
		size_t i = 0;
		size_t h = hasha<KeyType>(key, inf_);
		while (!data_[(h + i) % capacity_].isNull() && data_[(h + i) % capacity_].key_ != key) {
			inf_.op(3);
			i++;
			if (i >= capacity_) {
				throw std::runtime_error("Too much lines in hash table");
			}
		}
		inf_.op();
		if (data_[(h + i) % capacity_].isNull()) {
			return -1;
		}
		return (h + i) % capacity_;
	}
	std::vector<ValueWithState> data_;
	size_t capacity_;
	Informer inf_;
};

template <typename KeyType, typename ValueType>
class OrdTable {
public:
	OrdTable(std::ostream& stream = std::cout) : inf_(Table::kOrd, stream), tree_(inf_) {}
	ValueType* find(const KeyType& key) {
		ValueType* res = tree_.find(key);
		inf_.inform(TableOps::kFind);
		return res;
	}
	void insert(const KeyType& key, const ValueType& value) {
		tree_.insert(key, value);
		inf_.inform(TableOps::kPush);
	}
	void pop(const KeyType& key) {
		tree_.remove(key);
		inf_.inform(TableOps::kPop);
	}
private:
	AVLTree<KeyType, ValueType> tree_;
	Informer inf_;
};

template <typename KeyType, typename ValueType>
class UnordTable {
public:
	UnordTable(std::ostream& stream = std::cout) : lines_(), inf_(Table::kUnord, stream) {}
	ValueType* find(const KeyType& key) {
		for (size_t i = 0; i < lines_.size(); i++) {
			inf_.op();
			if (lines_[i].key_ == key) {
				inf_.inform(TableOps::kFind);
				return &lines_[i].value_;
			}
		}
		inf_.inform(TableOps::kFind);
		return nullptr;
	}
	void insert(const KeyType& key, const ValueType& value) {
		inf_.switchInform();
		// turn off find informing
		if (find(key) != nullptr) {
			inf_.switchInform();
			inf_.inform(TableOps::kPush);
			throw std::invalid_argument("Table already has this key");
		}
		// back
		inf_.switchInform();
		inf_.op();
		lines_.push_back({ key, value });
		inf_.inform(TableOps::kPush);
	}
	void pop(const KeyType& key) {
		for (size_t i = 0; i < lines_.size(); i++) {
			inf_.op(1);
			if (lines_[i].key_ == key) {
				inf_.op(2);
				lines_[i] = lines_[lines_.size() - 1];
				lines_.pop_back();
				inf_.inform(TableOps::kPop);
				return;
			}
		}
		inf_.inform(TableOps::kPop);
		throw std::invalid_argument("Table doesn't have this key");
	}
private:
	struct UnordTableUnit {
		KeyType key_;
		ValueType value_;
	};
	std::vector<UnordTableUnit> lines_;
	Informer inf_;
};
