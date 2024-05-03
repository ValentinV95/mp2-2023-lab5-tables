#include <gtest.h>
#include "tables.hpp"

TEST(UnordTable, can_create_unordered_table) {
	using utable = UnordTable<int, int>;
	ASSERT_NO_THROW(utable a);
}

TEST(UnordTable, can_insert) {
	UnordTable<int, int> a;
	ASSERT_NO_THROW(a.insert(1, 2));
}

TEST(UnordTable, can_delete) {
	UnordTable<int, int> a;
	a.insert(1, 2);
	ASSERT_NO_THROW(a.pop(1));
}

TEST(UnordTable, cant_delete_non_existent) {
	UnordTable<int, int> a;
	ASSERT_ANY_THROW(a.pop(1));
}

TEST(UnordTable, can_find) {
	UnordTable<int, int> a;
	a.insert(1, 2);
	ASSERT_NO_THROW(a.find(1));
}

TEST(UnordTable, can_find_correctly) {
	UnordTable<int, int> a;
	a.insert(1, 2);
	EXPECT_EQ(*a.find(1), 2);
}

TEST(OrdTable, can_create_ordered_table) {
	using otable = OrdTable<int, int>;
	ASSERT_NO_THROW(otable a);
}

TEST(OrdTable, can_insert) {
	OrdTable<int, int> a;
	ASSERT_NO_THROW(a.insert(1, 2));
}

TEST(OrdTable, can_delete) {
	OrdTable<int, int> a;
	a.insert(1, 2);
	ASSERT_NO_THROW(a.pop(1));
}

TEST(OrdTable, cant_delete_non_existent) {
	OrdTable<int, int> a;
	ASSERT_ANY_THROW(a.pop(1));
}

TEST(OrdTable, can_find) {
	OrdTable<int, int> a;
	a.insert(1, 2);
	ASSERT_NO_THROW(a.find(1));
}

TEST(OrdTable, can_find_correctly) {
	OrdTable<int, int> a;
	a.insert(1, 2);
	EXPECT_EQ(*a.find(1), 2);
}

TEST(HashTable, can_create_hash_table) {
	using htable = HashTable<int, int>;
	ASSERT_NO_THROW(htable a(100));
}

TEST(HashTable, can_insert) {
	HashTable<int, int> a(100);
	ASSERT_NO_THROW(a.insert(1, 2));
}

TEST(HashTable, can_delete) {
	HashTable<int, int> a(100);
	a.insert(1, 2);
	ASSERT_NO_THROW(a.pop(1));
}

TEST(HashTable, cant_delete_non_existent) {
	HashTable<int, int> a(100);
	ASSERT_ANY_THROW(a.pop(1));
}

TEST(HashTable, can_find) {
	HashTable<int, int> a(100);
	a.insert(1, 2);
	ASSERT_NO_THROW(a.find(1));
}

TEST(HashTable, can_find_correctly) {
	HashTable<int, int> a(100);
	a.insert(1, 2);
	EXPECT_EQ(*a.find(1), 2);
}
