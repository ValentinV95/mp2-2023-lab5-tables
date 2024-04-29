#include <gtest.h>
#include "table.h"
#include "unordered_table.h"

TEST(UnorderedTable, can_create)
{
	ASSERT_NO_THROW(unordered_table<int> ut);
}

TEST(UnorderedTable, can_copy)
{
	unordered_table<int> ut1;
	ASSERT_NO_THROW(unordered_table<int> ut2 = ut1);
}

TEST(UnorderedTable, can_assign)
{
	unordered_table<int> ut1;
	unordered_table<int> ut2;

	ASSERT_NO_THROW(ut2 = ut1);
}

TEST(UnorderedTable, copied_tables_have_own_memory)
{
	unordered_table<int> ut1;
	ut1.insert({ "test", 42 });
	unordered_table<int> ut2 = ut1;
	EXPECT_NE(ut1.find("test"), ut2.find("test"));
}

TEST(UnorderedTable, assigned_tables_have_own_memory)
{
	unordered_table<int> ut1, ut2;
	ut1.insert({"test", 42});
	ut2.insert({"ok", 54});
	ut2 = ut1;
	EXPECT_NE(ut1.find("test"), ut2.find("test"));
}

TEST(UnorderedTable, can_use_find)
{
	unordered_table<int> ut;
	ASSERT_NO_THROW(ut.find("test"));
}

TEST(UnorderedTable, can_search_nonexistent_element)
{
	unordered_table<int> ut;
	EXPECT_EQ(nullptr, ut.find("test"));
}

TEST(UnorderedTable, can_find_element_in_table)
{
	unordered_table<int> ut;
	ut.insert({"test", 42});
	EXPECT_EQ(42, *ut.find("test"));
}

TEST(UnorderedTable, can_insert)
{
	unordered_table<int> ut;
	ASSERT_NO_THROW(ut.insert({"test", 42}));
}

TEST(UnorderedTable, insert_changes_size)
{
	unordered_table<int> ut;
	ut.insert({ "test", 42 });
	EXPECT_EQ(1, ut.size());
}

TEST(UnorderedTable, can_remove)
{
	unordered_table<int> ut;
	ASSERT_NO_THROW(ut.remove("test"));
}

TEST(UnorderedTable, can_remove_nonexistent)
{
	unordered_table<int> ut;
	ut.insert({ "test", 42 });
	ASSERT_NO_THROW(ut.remove("foo"));
}

TEST(UnorderedTable, remove_changes_size)
{
	unordered_table<int> ut;
	ut.insert({ "test", 42 });
	ut.remove("test");
	EXPECT_EQ(0, ut.size());
}

TEST(UnorderedTable, remove_from_empty_table_doesnt_change_size)
{
	unordered_table<int> ut;
	ut.remove("test");
	EXPECT_EQ(0, ut.size());
}

TEST(UnorderedTable, cant_find_removed_element)
{
	unordered_table<int> ut;
	ut.insert({ "test1", 42 });
	ut.insert({ "test2", 54 });
	ut.insert({ "test3", 78 });
	ut.remove("test2");
	EXPECT_EQ(nullptr, ut.find("test2"));
}

TEST(UnorderedTable, can_check_emptiness)
{
	unordered_table<int> ut;
	ASSERT_TRUE(ut.empty());
	ut.insert({ "test", 42 });
	ASSERT_FALSE(ut.empty());
}

/*
TEST(UnorderedTable, can_create_map)
{
	using table = Table<int, int, unordered_table>;
	ASSERT_NO_THROW(table t);
}
*/