#include <gtest.h>

#include "polynoms.hpp"

TEST(List, can_create_empty_list) {
	ASSERT_NO_THROW(List<int> a);
}

TEST(List, can_copy_list) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 2);
	}
	ASSERT_NO_THROW(List<int> b(a));
}

TEST(List, can_copy_list_correctly) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 2);
	}
	List<int> b(a);
	EXPECT_EQ(a, b);
}

TEST(List, equality_test) {
	List<int> a;
	List<int> b;
	List<int> c;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 2);
		b.push_back(i + 2);
		c.push_back(i + 3);
	}
	EXPECT_EQ(a == b, true);
	EXPECT_EQ(a == c, false);
}

TEST(List, inequality_test) {
	List<int> a;
	List<int> b;
	List<int> c;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 2);
		b.push_back(i + 2);
		c.push_back(i + 3);
	}
	EXPECT_EQ(a != b, false);
	EXPECT_EQ(a != c, true);
}

TEST(List, can_assign_lists) {
	List<int> a;
	List<int> b;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	ASSERT_NO_THROW(b = a);
}

TEST(List, can_assign_lists_correctly) {
	List<int> a;
	List<int> b;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	b = a;
	EXPECT_EQ(a, b);
}

TEST(List, self_assignment) {
	List<int> a;
	a.push_back(3);
	ASSERT_NO_THROW(a = a);
}

TEST(List, can_get_element) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	for (size_t i = 0; i < 10; i++) {
		ASSERT_NO_THROW(a[i]);
	}
}

TEST(List, can_get_element_correctly) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(a[i], i + 10);
	}
}

TEST(List, throws_when_getting_out_of_range_elem) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	ASSERT_ANY_THROW(a[10]);
}

TEST(List, can_pop) {
	List<int> a;
	a.push_back(1);
	ASSERT_NO_THROW(a.pop(0));
}

TEST(List, can_pop_correctly) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 10);
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(a[0], i + 10);
		a.pop(0);
	}
	for (size_t i = 0; i < 10; i++) {
		a.push_back(i + 1);
	}
	for (size_t i = 0; i < 10; i++) {
		a.pop(9 - i);
		ASSERT_ANY_THROW(a[9-i]);
	}
	EXPECT_EQ(a.get_size(), 0);
}

TEST(List, throw_when_pop_empty) {
	List<int> a;
	ASSERT_ANY_THROW(a.pop(0));
}

TEST(List, throws_when_pop_out_of_range) {
	List<int> a;
	a.push_back(1);
	ASSERT_ANY_THROW(a.pop(99));
}

TEST(List, can_get_size) {
	List<int> a;
	ASSERT_NO_THROW(a.get_size());
}

TEST(List, can_get_size_correctly) {
	List<int> a;
	a.push_back(2);
	a.push_back(3);
	EXPECT_EQ(a.get_size(), 2);
}

TEST(List, can_push) {
	List<int> a;
	ASSERT_NO_THROW(a.push_back(1));
}

TEST(List, can_push_correctly) {
	List<int> a;
	for (size_t i = 0; i < 10; i++) {
		a.push(i, i + 10);
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(a[i], i + 10);
	}
	List<int> b;
	for (size_t i = 0; i < 10; i++) {
		b.push(0, i + 10);
	}
	for (int i = 9; i >= 0; i--) {
		EXPECT_EQ(a[i], i + 10);
	}
}

TEST(List, throws_when_push_out_of_range) {
	List<int> a;
	ASSERT_ANY_THROW(a.push(1, 2));
}
