// table_rec.h contains a template struct to be used with table containers

#ifndef TABLE_REC_H
#define TABLE_REC_H

template<class T>
struct TableRec
{
	std::string key;
	T val;

	TableRec() : key(), val() {}
	TableRec(const std::string& k, const T& v) : key(k), val(v) {}
	TableRec(const TableRec& tr) : key(tr.key), val(tr.val) {}
	TableRec(TableRec&& tr) noexcept : key(tr.key), val(tr.val) {}
	TableRec& operator=(const TableRec& tr) = default;
	TableRec& operator=(TableRec&& tr) = default;

	bool operator==(const TableRec& tr) { return key == tr.key; }
	bool operator!=(const TableRec& tr) { return key != tr.key; }
	bool operator<(const TableRec& tr) { return key < tr.key; }
	bool operator<=(const TableRec& tr) { return key <= tr.key; }
	bool operator>(const TableRec& tr) { return key > tr.key; }
	bool operator>=(const TableRec& tr) { return key >= tr.key; }
};

#endif