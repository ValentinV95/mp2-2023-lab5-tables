// тесты для стека

#include "stack.hpp"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_copy_stack)
{
	TStack<int> s;
	ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_class_has_own_memory)
{
	TStack<int> s;
	s.push(11);
	TStack<int> s1(s);
	s1.push(2);
	EXPECT_NE(s1.top(), s.top());
}

TEST(TStack, can_assign_stack)
{
	TStack<int> s, s1;
	ASSERT_NO_THROW(s1 = s);
}

TEST(TStack, can_do_self_assignment)
{
	TStack<int> s;
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, assignment_operator_assigns_size)
{
	TStack<int> s, s1;
	s.push(1);
	s.push(2);
	s1 = s;
	EXPECT_EQ(s.get_size(), s1.get_size());
}

TEST(TStack, can_push_element)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.push(1900));
}

TEST(TStack, can_pop_element)
{
	TStack<int> s;
	s.push(-9);
	ASSERT_NO_THROW(s.pop());
}

TEST(TStack, cant_pop_if_empty_stack)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, can_get_top_element)
{
	TStack<int> s;
	s.push(2);
	ASSERT_NO_THROW(s.top());
}

TEST(TStack, top_element_changes_on_push)
{
	TStack<int> s;
	s.push(1);
	s.push(2);
	EXPECT_EQ(2, s.top());
}

TEST(TStack, top_element_changes_on_pop)
{
	TStack<int> s;
	s.push(1);
	s.push(2);
	s.pop();
	EXPECT_EQ(1, s.top());
}

TEST(TStack, cant_get_top_if_empty_stack)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.top());
}

TEST(TStack, stack_size_returns_zero_if_empty_stack)
{
	TStack<int> s;
	ASSERT_EQ(0, s.get_size());
}

TEST(TStack, stack_size_increases_on_push)
{
	TStack<int> s;
	s.push(1);
	ASSERT_EQ(1, s.get_size());
}

TEST(TStack, stack_size_decreases_on_pop)
{
	TStack<int> s;
	s.push(1);
	s.push(2);
	s.pop();
	ASSERT_EQ(1, s.get_size());
}

TEST(TStack, isempty_returns_true_if_empty)
{
	TStack<int> s;
	ASSERT_TRUE(s.isEmpty());
}

TEST(TStack, isempty_returns_false_if_not_empty)
{
	TStack<int> s;
	s.push(1337);
	ASSERT_FALSE(s.isEmpty());
}
