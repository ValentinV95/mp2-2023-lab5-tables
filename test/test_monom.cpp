#include <gtest.h>

#include "polynoms.hpp"

TEST(Monom, can_create_monom) {
	char degs[3] = { 5, 2, 0 };
	ASSERT_NO_THROW(Monom(2.0, degs));
}

TEST(Monom, cant_create_monom_with_invalid_degrees) {
	char degs[3] = { 5, 10, -2 };
	ASSERT_ANY_THROW(Monom(2.0, degs));
}

TEST(Monom, can_copy) {
	char degs[3] = { 5, 2, 0 };
	Monom a(2.0, degs);
	ASSERT_NO_THROW(Monom b(a));
}

TEST(Monom, can_copy_correctly) {
	char degs[3] = { 5, 2, 0 };
	Monom a(2.0, degs);
	Monom b(a);
	EXPECT_EQ(a, b);
}

TEST(Monom, equality_test) {
	char degs[3] = { 5, 2, 0 };
	char degs1[3] = { 5, 2, 1 };
	Monom a(3.0, degs);
	Monom b(3.0, degs);
	Monom c(3.0, degs1);
	EXPECT_EQ(a == b, true);
	EXPECT_EQ(a == c, false);
}

TEST(Monom, inequality_test) {
	char degs[3] = { 5, 2, 0 };
	char degs1[3] = { 5, 2, 1 };
	Monom a(3.0, degs);
	Monom b(3.0, degs);
	Monom c(3.0, degs1);
	EXPECT_EQ(a != b, false);
	EXPECT_EQ(a != c, true);
}

TEST(Monom, can_multiply) {
	char degs[3] = { 5, 2, 0 };
	char degs1[3] = { 1, 5, 2 };
	Monom a(2.0, degs);
	Monom b(3.0, degs1);
	ASSERT_NO_THROW(a * b);
}

TEST(Monom, can_multiply_correctly) {
	Monom a(2.0, 520);
	Monom b(3.0, 152);
	Monom c(6.0, 672);
	EXPECT_EQ(a * b, c);
}
