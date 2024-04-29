#include <gtest.h>
#include "table.h"
#include "hash_table.h"

TEST(HashTable, can_create)
{
	ASSERT_NO_THROW(hash_table<int> ht);
}

TEST(HashTable, can_copy)
{
	hash_table<int> ht1;
	ASSERT_NO_THROW(hash_table<int> ht2 = ht1);
}

TEST(HashTable, can_assign)
{
	hash_table<int> ht1;
	hash_table<int> ht2;

	ASSERT_NO_THROW(ht2 = ht1);
}

TEST(HashTable, copied_tables_have_own_memory)
{
	hash_table<int> ht1;
	ht1.insert({ "test", 42 });
	hash_table<int> ht2 = ht1;
	EXPECT_NE(ht1.find("test"), ht2.find("test"));
}

TEST(HashTable, assigned_tables_have_own_memory)
{
	hash_table<int> ht1, ht2;
	ht1.insert({ "test", 42 });
	ht2.insert({ "ok", 54 });
	ht2 = ht1;
	EXPECT_NE(ht1.find("test"), ht2.find("test"));
}

TEST(HashTable, can_use_find)
{
	hash_table<int> ht;
	ASSERT_NO_THROW(ht.find("test"));
}

TEST(HashTable, can_search_nonexistent_element)
{
	hash_table<int> ht;
	EXPECT_EQ(nullptr, ht.find("test"));
}

TEST(HashTable, can_find_element_in_table)
{
	hash_table<int> ht;
	ht.insert({ "test", 42 });
	EXPECT_EQ(42, *ht.find("test"));
}

TEST(HashTable, can_insert)
{
	hash_table<int> ht;
	ASSERT_NO_THROW(ht.insert({ "test", 42 }));
}

TEST(HashTable, insert_changes_size)
{
	hash_table<int> ht;
	ht.insert({ "test", 42 });
	EXPECT_EQ(1, ht.size());
}

TEST(HashTable, can_remove)
{
	hash_table<int> ht;
	ASSERT_NO_THROW(ht.remove("test"));
}

TEST(HashTable, can_remove_nonexistent)
{
	hash_table<int> ht;
	ht.insert({ "test", 42 });
	ASSERT_NO_THROW(ht.remove("foo"));
}

TEST(HashTable, remove_changes_size)
{
	hash_table<int> ht;
	ht.insert({ "test", 42 });
	ht.remove("test");
	EXPECT_EQ(0, ht.size());
}

TEST(HashTable, remove_from_empty_table_doesnt_change_size)
{
	hash_table<int> ht;
	ht.remove("test");
	EXPECT_EQ(0, ht.size());
}

TEST(HashTable, cant_find_removed_element)
{
	hash_table<int> ht;
	ht.insert({ "test1", 42 });
	ht.insert({ "test2", 54 });
	ht.insert({ "test3", 78 });
	ht.remove("test2");
	EXPECT_EQ(nullptr, ht.find("test2"));
}

TEST(HashTable, can_check_emptiness)
{
	hash_table<int> ht;
	ASSERT_TRUE(ht.empty());
	ht.insert({ "test", 42 });
	ASSERT_FALSE(ht.empty());
}