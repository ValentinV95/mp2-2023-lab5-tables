#include "informer.hpp"

void Informer::inform(TableOps operation) {
	if (canInform_ == false) {
		return;
	}
	switch (tableType_) {
	case Table::kUnord:
		stream << "Unordered ";
		break;
	case Table::kOrd:
		stream << "Ordered ";
		break;
	case Table::kHash:
		stream << "Hash ";
		break;
	default:
		throw std::runtime_error("Table type is not supported");
	}
	stream << "table ";
	switch (operation) {
	case TableOps::kPush:
		stream << "push ";
		break;
	case TableOps::kFind:
		stream << "find ";
		break;
	case TableOps::kPop:
		stream << "pop ";
		break;
	default:
		throw std::runtime_error("Operation type is not supported");
	}
	stream << "was recorded. " << "Operations: " << operCount_ << "." << std::endl;
	operCount_ = 0;
}
