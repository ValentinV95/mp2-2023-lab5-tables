#include "list.h"
#include <algorithm>
#include <gtest.h>

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> l);
}

TEST(List, can_copy_list)
{
	List<int> l1;
	ASSERT_NO_THROW(List<int>(l2));
}

TEST(List, copied_lists_are_equal)
{
	List<int> l1;
	for (int i = 0; i < 50; i++)
		l1.insert(i);
	List<int> l2(l1);
	EXPECT_EQ(l1, l2);
}

TEST(List, copied_list_has_own_memory)
{
	List<int> l1;
	l1.insert(1);
	l1.insert(2);
	l1.insert(3);

	List<int> l2(l1);
	l2.insert(4);

	EXPECT_NE(l1, l2);
}

TEST(List, copied_lists_have_same_size)
{
	List<int> l1;
	l1.insert(42);

	List<int> l2(l1);
	EXPECT_EQ(l1.size(), l2.size());
}

TEST(List, can_assign)
{
	List<int> l1;
	List<int> l2;
	ASSERT_NO_THROW(l2 = l1);
}

TEST(List, assigned_lists_are_equal)
{
	List<int> l1;
	l1.insert(42);
	l1.insert(43);
	List<int> l2;
	l2.insert(54);

	l2 = l1;
	EXPECT_EQ(l1, l2);
}

TEST(List, assigned_lists_have_equal_sizes)
{
	List<int> l1;
	l1.insert(42);
	l1.insert(43);
	List<int> l2;
	l2.insert(54);

	l2 = l1;
	EXPECT_EQ(l1.size(), l2.size());
}

TEST(List, can_insert)
{
	List<int> l;
	ASSERT_NO_THROW(l.insert(42));
}

TEST(List, insert_changes_size)
{
	List<int> l;
	l.insert(4);
	EXPECT_EQ(1, l.size());
}

TEST(List, can_insert_after)
{
	List<int> l;
	l.insert(41);
	l.insert(42);
	l.insert(43);

	auto it = l.begin();
	++it;
	l.insertAfter(it, 999);

	EXPECT_EQ(999, *(++it));
}

TEST(List, insert_after_changes_size)
{
	List<int> l;
	l.insert(41);
	l.insert(42);
	l.insert(43);
	l.insertAfter(++l.begin(), 999);

	EXPECT_EQ(4, l.size());
}

TEST(List, can_erase_from_front)
{
	List<int> l;
	l.insert(42);
	ASSERT_NO_THROW(l.pop());
	ASSERT_NO_THROW(l.pop());
	ASSERT_NO_THROW(l.pop());
}

TEST(List, erase_changes_size)
{
	List<int> l;
	l.insert(42);
	l.insert(42);
	l.pop();
	EXPECT_EQ(1, l.size());
	l.pop();
	EXPECT_EQ(0, l.size());
	l.pop();
	EXPECT_EQ(0, l.size());
}

TEST(List, can_erase_after)
{
	List<int> l;
	l.insert(41);
	l.insert(42);
	l.insert(999);
	l.insert(43);

	auto it = l.begin();
	l.eraseAfter(it);

	EXPECT_EQ(42, *(++it));
}

TEST(List, can_erase_after_in_empty_list)
{
	List<int> l;
	ASSERT_NO_THROW(l.eraseAfter(l.before_begin()));
	ASSERT_NO_THROW(l.eraseAfter(l.before_begin()));
}

TEST(List, erase_after_dont_change_size_of_empty_list)
{
	List<int> l;
	l.eraseAfter(l.before_begin());
	EXPECT_EQ(0, l.size());
}

TEST(List, erase_after_changes_size)
{
	List<int> l;
	l.insert(41);
	l.insert(42);
	l.insert(999);
	l.insert(43);
	l.eraseAfter(l.begin());
	EXPECT_EQ(3, l.size());
}

TEST(List, pop_doesnt_throw_on_empty_list)
{
	List<int> l;
	ASSERT_NO_THROW(l.pop());
}

TEST(List, isempty_returns_true_on_empty_list)
{
	List<int> l;
	EXPECT_TRUE(l.isEmpty());
}

TEST(List, isempty_returns_false_when_list_is_not_empty)
{
	List<int> l;
	l.insert(2);
	EXPECT_FALSE(l.isEmpty());
}

TEST(List, can_use_arrow_operator)
{
	struct SomeStruct
	{
		int n;
		double d;
	};

	List<SomeStruct> l;
	l.insert({ 42, 3.14 });
	auto it = l.begin();
	ASSERT_EQ(42, it->n);
	ASSERT_EQ(3.14, it->d);
}

TEST(List, can_prefix_increment)
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l.insert(i);

	auto it = l.begin();
	++it;
	EXPECT_EQ(8, *it);
}

TEST(List, can_postfix_increment)
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l.insert(i);

	auto it = l.begin();
	ASSERT_EQ(9, *(it++));
	ASSERT_EQ(8, *it);
}

TEST(List, can_change_keyue_via_iterator)
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l.insert(i);
	*l.begin() = 42;

	EXPECT_EQ(42, *l.begin());
}

TEST(List, can_use_list_iterator_with_std_functions)
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l.insert(i);

	std::fill(l.begin(), l.end(), -1);
	ASSERT_EQ(10, l.size());

	for (auto&& el : l)
		ASSERT_EQ(-1, el);
}

TEST(List, equality_returns_true_on_equal_lists)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(42);
	EXPECT_TRUE(p1 == p2);
}

TEST(List, equality_returns_false_on_unequal_lists)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(43);
	EXPECT_FALSE(p1 == p2);
}

TEST(List, equality_returns_false_when_lists_have_different_size)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(42);
	p2.insert(42);
	EXPECT_FALSE(p1 == p2);
}

TEST(List, inequality_returns_false_on_equal_lists)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(42);
	EXPECT_FALSE(p1 != p2);
}

TEST(List, inequality_returns_true_on_unequal_lists)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(43);
	EXPECT_TRUE(p1 != p2);
}

TEST(List, inequality_returns_true_when_lists_have_different_size)
{
	List<int> p1;
	p1.insert(42);
	List<int> p2;
	p2.insert(42);
	p2.insert(42);
	EXPECT_TRUE(p1 != p2);
}