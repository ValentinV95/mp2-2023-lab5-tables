#include <gtest.h>
#include "table.h"
#include "ordered_table.h"

TEST(OrderedTable, can_create)
{
	ASSERT_NO_THROW(ordered_table<int> ot);
}

TEST(OrderedTable, can_copy)
{
	ordered_table<int> ot1;
	ASSERT_NO_THROW(ordered_table<int> ot2 = ot1);
}

TEST(OrderedTable, can_assign)
{
	ordered_table<int> ot1;
	ordered_table<int> ot2;

	ASSERT_NO_THROW(ot2 = ot1);
}

TEST(OrderedTable, copied_tables_have_own_memory)
{
	ordered_table<int> ot1;
	ot1.insert({ "test", 42 });
	ordered_table<int> ot2 = ot1;
	EXPECT_NE(ot1.find("test"), ot2.find("test"));
}

TEST(OrderedTable, assigned_tables_have_own_memory)
{
	ordered_table<int> ot1, ot2;
	ot1.insert({ "test", 42 });
	ot2.insert({ "ok", 54 });
	ot2 = ot1;
	EXPECT_NE(ot1.find("test"), ot2.find("test"));
}

TEST(OrderedTable, can_use_find)
{
	ordered_table<int> ot;
	ASSERT_NO_THROW(ot.find("test"));
}

TEST(OrderedTable, can_search_nonexistent_element)
{
	ordered_table<int> ot;
	EXPECT_EQ(nullptr, ot.find("test"));
}

TEST(OrderedTable, can_find_element_in_table)
{
	ordered_table<int> ot;
	ot.insert({ "test", 42 });
	ot.insert({ "uf", 454 });
	ot.insert({ "a", 3466 });
	ot.insert({ "yrd", 34 });
	ot.insert({ "aaa", -999 });
	EXPECT_EQ(42, *ot.find("test"));
}

TEST(OrderedTable, can_insert)
{
	ordered_table<int> ot;
	ASSERT_NO_THROW(ot.insert({ "test", 42 }));
}

TEST(OrderedTable, insert_changes_size)
{
	ordered_table<int> ot;
	ot.insert({ "test", 42 });
	EXPECT_EQ(1, ot.size());
}

TEST(OrderedTable, can_remove)
{
	ordered_table<int> ot;
	ASSERT_NO_THROW(ot.remove("test"));
}

TEST(OrderedTable, can_remove_nonexistent)
{
	ordered_table<int> ot;
	ot.insert({ "test", 42 });
	ASSERT_NO_THROW(ot.remove("foo"));
}

TEST(OrderedTable, remove_changes_size)
{
	ordered_table<int> ot;
	ot.insert({ "test", 42 });
	ot.remove("test");
	EXPECT_EQ(0, ot.size());
}

TEST(OrderedTable, remove_from_empty_table_doesnt_change_size)
{
	ordered_table<int> ot;
	ot.remove("test");
	EXPECT_EQ(0, ot.size());
}

TEST(OrderedTable, cant_find_removed_element)
{
	ordered_table<int> ot;
	ot.insert({ "test1", 42 });
	ot.insert({ "test2", 54 });
	ot.insert({ "test3", 78 });
	ot.remove("test2");
	EXPECT_EQ(nullptr, ot.find("test2"));
}

TEST(OrderedTable, can_check_emptiness)
{
	ordered_table<int> ot;
	ASSERT_TRUE(ot.empty());
	ot.insert({ "test", 42 });
	ASSERT_FALSE(ot.empty());
}