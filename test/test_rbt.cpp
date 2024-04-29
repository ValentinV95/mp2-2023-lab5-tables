#include <gtest.h>
#include "table.h"
#include "rbt.h"

TEST(RedBlackTree, can_create)
{
	ASSERT_NO_THROW(rbtree<int> rbt);
}

TEST(RedBlackTree, can_copy)
{
	rbtree<int> rbt1;
	ASSERT_NO_THROW(rbtree<int> rbt2 = rbt1);
}

TEST(RedBlackTree, can_assign)
{
	rbtree<int> rbt1;
	rbtree<int> rbt2;

	ASSERT_NO_THROW(rbt2 = rbt1);
}

TEST(RedBlackTree, copied_tables_have_own_memory)
{
	rbtree<int> rbt1;
	rbt1.insert({ "test", 42 });
	rbtree<int> rbt2 = rbt1;
	EXPECT_NE(rbt1.find("test"), rbt2.find("test"));
}

TEST(RedBlackTree, assigned_tables_have_own_memory)
{
	rbtree<int> rbt1, rbt2;
	rbt1.insert({ "test", 42 });
	rbt2.insert({ "ok", 54 });
	rbt2 = rbt1;
	EXPECT_NE(rbt1.find("test"), rbt2.find("test"));
}

TEST(RedBlackTree, can_use_find)
{
	rbtree<int> rbt;
	ASSERT_NO_THROW(rbt.find("test"));
}

TEST(RedBlackTree, can_search_nonexistent_element)
{
	rbtree<int> rbt;
	EXPECT_EQ(nullptr, rbt.find("test"));
}

TEST(RedBlackTree, can_find_element_in_table)
{
	rbtree<int> rbt;
	rbt.insert({ "test", 42 });
	EXPECT_EQ(42, *rbt.find("test"));
}

TEST(RedBlackTree, can_insert)
{
	rbtree<int> rbt;
	ASSERT_NO_THROW(rbt.insert({ "test", 42 }));
}

TEST(RedBlackTree, insert_changes_size)
{
	rbtree<int> rbt;
	rbt.insert({ "test", 42 });
	EXPECT_EQ(1, rbt.size());
}

TEST(RedBlackTree, can_remove)
{
	rbtree<int> rbt;
	ASSERT_NO_THROW(rbt.remove("test"));
}

TEST(RedBlackTree, can_remove_nonexistent)
{
	rbtree<int> rbt;
	rbt.insert({ "test", 42 });
	ASSERT_NO_THROW(rbt.remove("foo"));
}

// Removing head without children nodes
TEST(RedBlackTree, remove_case_1)
{
	rbtree<int> rbt;
	rbt.insert({ "test", 42 });
	ASSERT_NO_THROW(rbt.remove("test"));
}

// Removing head with one child
TEST(RedBlackTree, remove_case_2)
{
	rbtree<int> rbt;
	rbt.insert({ "a", 43 });
	rbt.insert({ "test", 42 });
	ASSERT_NO_THROW(rbt.remove("a"));
}

// Removing node without children
TEST(RedBlackTree, remove_case_3)
{
	rbtree<int> rbt;
	rbt.insert({ "a", 43 });
	rbt.insert({ "test", 42 });
	ASSERT_NO_THROW(rbt.remove("test"));
}

// Removing node with one child
TEST(RedBlackTree, remove_case_4)
{
	rbtree<int> rbt;
	rbt.insert({ "a", 43 });
	rbt.insert({ "test1", 42 });
	rbt.insert({ "test2", 42 });
	rbt.insert({ "test3", 42 });
	ASSERT_NO_THROW(rbt.remove("test2"));
}

// Removing head with two children
TEST(RedBlackTree, remove_case_5)
{
	rbtree<int> rbt;
	rbt.insert({ "a", 43 });
	rbt.insert({ "test1", 42 });
	rbt.insert({ "test2", 42 });
	ASSERT_NO_THROW(rbt.remove("a"));
}

// Removing node with two children
TEST(RedBlackTree, remove_case_6)
{
	rbtree<int> rbt;
	rbt.insert({ "a", 43 });
	rbt.insert({ "test1", 42 });
	rbt.insert({ "test2", 42 });
	rbt.insert({ "test3", 42 });
	rbt.insert({ "test4", 42 });
	ASSERT_NO_THROW(rbt.remove("test3"));
}

TEST(RedBlackTree, remove_changes_size)
{
	rbtree<int> rbt;
	rbt.insert({ "test", 42 });
	rbt.remove("test");
	EXPECT_EQ(0, rbt.size());
}

TEST(RedBlackTree, remove_from_empty_table_doesnt_change_size)
{
	rbtree<int> rbt;
	rbt.remove("test");
	EXPECT_EQ(0, rbt.size());
}

TEST(RedBlackTree, cant_find_removed_element)
{
	rbtree<int> rbt;
	rbt.insert({ "test1", 42 });
	rbt.insert({ "test2", 54 });
	rbt.insert({ "test3", 78 });
	rbt.remove("test2");
	EXPECT_EQ(nullptr, rbt.find("test2"));
}

TEST(RedBlackTree, can_check_emptiness)
{
	rbtree<int> rbt;
	ASSERT_TRUE(rbt.empty());
	rbt.insert({ "test", 42 });
	ASSERT_FALSE(rbt.empty());
}