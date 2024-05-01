#include "gtest.h"
#include "HashTable.h"
#include "Polynom.h"
#include <string>

TEST(HashTable, can_create_hash_table) {
	ASSERT_NO_THROW(HashTable T);
}

TEST(HashTable, can_add_an_element) {
	HashTable T;
	ASSERT_NO_THROW(T.add("pol1", Polynom("1+x")));
}

TEST(HashTable, can_find_an_element_in_table) {
	HashTable T;
	T.add("pol1", Polynom("1+x"));
	ASSERT_NO_THROW(T.find("pol1"));
}

TEST(HashTable, throws_when_cant_find_an_element) {
	HashTable T;
	ASSERT_ANY_THROW(T.find("pol1"));
}

TEST(HashTable, find_is_correct) {
	HashTable T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	EXPECT_EQ(p, T.find("pol1"));
}

TEST(HashTable, can_delete) {
	HashTable T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	ASSERT_NO_THROW(T.del("pol1"));
}

TEST(HashTable, delete_is_correct) {
	HashTable T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	T.del("pol1");
	ASSERT_ANY_THROW(T.find("pol1"));
}