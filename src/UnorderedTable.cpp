#include "UnorderedTable.h"
#include "arithmetic.h"

UnorderedTable::UnorderedTable() : size(0) {}
UnorderedTable::UnorderedTable(UnorderedTable& T) {
	for (const auto& rec : T.table) {
		this->add(rec.first, rec.second);
	}
}
void UnorderedTable::add(std::string name, polynoms pol) {
	counttable = 0;
	try {
		search(name);
	}
	catch (std::logic_error& e) {
		table.push_back(make_pair(name, pol));
		size++;
		counttable++;
		return;
	}
	throw std::logic_error("This element already exists");
}
polynoms UnorderedTable::search(std::string name) {
	counttable = 0;
	int n = table.size();
	for (int i = 0; i < n; i++) {
		counttable++;
		if (table[i].first == name) {
			return table[i].second;
		}
	}
	throw std::logic_error("No such element is in table");

}
void UnorderedTable::clear(std::string name) {
	counttable = 0;
	int n = table.size();
	for (int i = 0; i < n; i++) {
		if (table[i].first == name) {
			table[i] = table[table.size() - 1];
			table.pop_back();
			size--;
			counttable++;
			return;
		}
	}
	throw std::logic_error("No such element is in table");

}
size_t UnorderedTable::getsize() {
	return size;
}
polynoms UnorderedTable::Arithmetic(std::string strexpr) {
	ArithmeticExpr expr(strexpr);
	expr.ToPostfix();
	std::vector<std::string> operands = expr.GetOperands();
	std::map<std::string, polynoms> values;
	for (int i = 0; i < operands.size(); i++) {
		if (operands[i][0] < '0' || operands[i][0]>'9') {
			values[operands[i]] = search(operands[i]);
		}
	}
	polynoms res = expr.Calculate(values);
	return res;
}

