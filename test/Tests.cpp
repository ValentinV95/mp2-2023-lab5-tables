#include "gtest.h"
#include "AVLTreeTable.h"
#include "UnorderedTable.h"
#include "HashTable.h"
using namespace std;

TEST(AVLTreeTable, can_create_table) {
	ASSERT_NO_THROW(AVLTreeTable T);
}
TEST(AVLTreeTable, can_copy_table) {
	AVLTreeTable T;
	ASSERT_NO_THROW(AVLTreeTable T2(T));
}
TEST(AVLTreeTable, can_add) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	ASSERT_NO_THROW(T.add("pol", A););
}
TEST(AVLTreeTable, can_searh) {
	list<pair<int, double>>a;
	string str = "pol";
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.search(str));
}
TEST(AVLTreeTable, copy_table_has_its_own_memory) {
	list<pair<int, double>>a;
	string str = "pol";
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	AVLTreeTable T2(T);
	T2.add("pol", A);
	ASSERT_ANY_THROW(T.search(str));
}
TEST(AVLTreeTable, search_and_add_are_correct) {
	list<pair<int, double>>a;
	string str = "pol";
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	T.add("pol", A);
	EXPECT_EQ(T.search(str), A);
}
TEST(AVLTreeTable, can_clear) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.clear("pol"));
}
TEST(AVLTreeTable, clear_is_correct) {
	list<pair<int, double>>a;
	string str = "pol";
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	AVLTreeTable T;
	T.add("pol", A);
	T.clear("pol");
	ASSERT_ANY_THROW(T.search(str));
}
TEST(AVLTreeTable, can_arithmetic) {
	list<pair<int, double>>a, b, c, d, a20;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	polynoms A(a), B(b), A20(a20), C(c), D(d);
	AVLTreeTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	ASSERT_NO_THROW(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"));
}
TEST(AVLTreeTable, arithmetic_is_correct) {
	list<pair<int, double>>a, b, c, d, a20, resmon;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(100, -5));
	resmon.push_back(make_pair(20, 2));
	resmon.push_back(make_pair(220, 4));
	resmon.push_back(make_pair(000, 8));
	polynoms A(a), B(b), A20(a20), C(c), D(d), res(resmon);
	AVLTreeTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	EXPECT_EQ(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"), res);
}


TEST(UnorderedTable, can_create_table) {
	ASSERT_NO_THROW(UnorderedTable T);
}
TEST(UnorderedTable, can_copy_table) {
	UnorderedTable T;
	ASSERT_NO_THROW(UnorderedTable T2(T));
}
TEST(UnorderedTable, can_add) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	UnorderedTable T;
	ASSERT_NO_THROW(T.add("pol", A););
}
TEST(UnorderedTable, can_searh) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	UnorderedTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.search(str));
}
TEST(UnorderedTable, copy_table_has_its_own_memory) {
	list<pair<int, double>>a;
	string str = "pol";
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	UnorderedTable T;
	UnorderedTable T2(T);
	T2.add("pol", A);
	ASSERT_ANY_THROW(T.search(str));
}

TEST(UnorderedTable, search_and_add_are_correct) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	UnorderedTable T;
	T.add("pol", A);
	EXPECT_EQ(T.search(str), A);
}
TEST(UnorderedTable, can_clear) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	UnorderedTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.clear(str));
}
TEST(UnorderedTable, clear_is_correct) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	UnorderedTable T;
	T.add("pol", A);
	T.clear("pol");
	ASSERT_ANY_THROW(T.search(str));
}
TEST(UnorderedTable, can_arithmetic) {
	list<pair<int, double>>a, b, c, d, a20;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	polynoms A(a), B(b), A20(a20), C(c), D(d);
	UnorderedTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	ASSERT_NO_THROW(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"));
}
TEST(UnorderedTable, arithmetic_is_correct) {
	list<pair<int, double>>a, b, c, d, a20, resmon;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(100, -5));
	resmon.push_back(make_pair(20, 2));
	resmon.push_back(make_pair(220, 4));
	resmon.push_back(make_pair(000, 8));
	polynoms A(a), B(b), A20(a20), C(c), D(d), res(resmon);
	UnorderedTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	EXPECT_EQ(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"), res);
}




TEST(HashTable, can_create_table) {
	ASSERT_NO_THROW(HashTable T);
}
TEST(HashTable, can_copy_table) {
	HashTable T;
	ASSERT_NO_THROW(HashTable T2(T));
}
TEST(HashTable, can_add) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	HashTable T;
	ASSERT_NO_THROW(T.add("pol", A););
}
TEST(HashTable, can_searh) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	HashTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.search(str));
}
TEST(HashTable, copy_table_has_its_own_memory) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	HashTable T;
	HashTable T2(T);
	T2.add("pol", A);
	ASSERT_ANY_THROW(T.search(str));
}
TEST(HashTable, search_and_add_are_correct) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	HashTable T;
	T.add("pol", A);
	EXPECT_EQ(T.search(str), A);
}
TEST(HashTable, can_clear) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	polynoms A(a);
	HashTable T;
	T.add("pol", A);
	ASSERT_NO_THROW(T.clear("pol"));
}
TEST(HashTable, clear_is_correct) {
	list<pair<int, double>>a;
	a.push_back(make_pair(100, 1));
	string str = "pol";
	polynoms A(a);
	HashTable T;
	T.add("pol", A);
	T.clear("pol");
	ASSERT_ANY_THROW(T.search(str));
}
TEST(HashTable, can_arithmetic) {
	list<pair<int, double>>a, b, c, d, a20;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	polynoms A(a), B(b), A20(a20), C(c), D(d);
	HashTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	ASSERT_NO_THROW(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"));
}
TEST(HashTable, arithmetic_is_correct) {
	list<pair<int, double>>a, b, c, d, a20, resmon;
	a.push_back(make_pair(100, 1));
	b.push_back(make_pair(20, 2));
	a20.push_back(make_pair(100, 1));
	c.push_back(make_pair(001, 1));
	d.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(111, 1));
	resmon.push_back(make_pair(100, -5));
	resmon.push_back(make_pair(20, 2));
	resmon.push_back(make_pair(220, 4));
	resmon.push_back(make_pair(000, 8));
	polynoms A(a), B(b), A20(a20), C(c), D(d), res(resmon);
	HashTable T;
	T.add("pol1", A);
	T.add("pol2", B);
	T.add("pol3", A20);
	T.add("pol4", C);
	T.add("sins", D);
	EXPECT_EQ(T.Arithmetic("sins+ln(1)*pol4+pol1+pol2-6*pol3+pol1*pol3*pol2+pol2*pol3*pol1+8"), res);
}