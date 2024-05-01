#pragma once
#include <iostream>

enum class Table {
	kUnord, kOrd, kHash
};
enum class TableOps {
	kPush, kFind, kPop
};

class Informer {
public:
	Informer(Table tableType, std::ostream& prefStream = std::cout) : operCount_(0), tableType_(tableType), stream(prefStream), canInform_(true) {}
	Informer(const Informer& c) = default;
	void inform(TableOps operation);
	void op(int count = 1) { operCount_ += count; }
	void switchInform() { canInform_ = !canInform_; }
private:
	bool canInform_;
	size_t operCount_;
	Table tableType_;
	std::ostream &stream;
};
