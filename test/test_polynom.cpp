#include <gtest.h>

#include "polynoms.hpp"

TEST(Polynom, can_create_empty_polynom) {
	ASSERT_NO_THROW(Polynom a);
}

TEST(Polynom, can_create_polynom_from_monoms_list) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 2, 4, 7 };
	monoms.push_back(Monom(2.3, degs));
	monoms.push_back(Monom(5.0, degs1));
	ASSERT_NO_THROW(Polynom a(monoms));
}

TEST(Polynom, can_self_subtract) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	monoms.push_back(Monom(2.3, degs));
	Polynom a(monoms);
	ASSERT_NO_THROW(a - a);
}

TEST(Polynom, can_add) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 2, 4, 7 };
	monoms.push_back(Monom(2.3, degs));
	monoms.push_back(Monom(5.0, degs1));
	Polynom a(monoms);
	List<Monom> monoms1;
	const char degs2[3] = { 9, 8, 7 };
	const char degs3[3] = { 7, 6, 5 };
	monoms1.push_back(Monom(5.0, degs2));
	monoms1.push_back(Monom(1.5, degs3));
	Polynom b(monoms1);
	ASSERT_NO_THROW(a + b);
}

TEST(Polynom, can_add_correctly) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 2, 4, 7 };
	monoms.push_back(Monom(2.3, degs));
	monoms.push_back(Monom(5.0, degs1));
	Polynom a(monoms);
	List<Monom> monoms1;
	const char degs2[3] = { 9, 8, 7 };
	const char degs3[3] = { 7, 6, 5 };
	monoms1.push_back(Monom(5.0, degs2));
	monoms1.push_back(Monom(1.5, degs3));
	Polynom b(monoms1);
	monoms.push_back(Monom(5.0, degs2));
	monoms.push_back(Monom(1.5, degs3));
	Polynom c(monoms);
	EXPECT_EQ(a + b, c);
}

TEST(Polynom, can_multiply_by_const) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	monoms.push_back(Monom(1.2, degs));
	Polynom a(monoms);
	ASSERT_NO_THROW(a * 2.2);
}

TEST(Polynom, can_multiply_by_const_correctly1) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	monoms.push_back(Monom(1.2, degs));
	Polynom a(monoms);
	monoms[0] = Monom(1.2 * 2.2, degs);
	Polynom b(monoms);
	a = a * 2.2;
	EXPECT_EQ(a, b);
}

TEST(Polynom, can_multiply_by_const_correctly2) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 6, 6, 5 };
	monoms.push_back(Monom(1.2, degs));
	monoms.push_back(Monom(5.0, degs1));
	Polynom a(monoms);
	monoms[0] = Monom(1.2 * (-2.2), degs);
	monoms[1] = Monom(5.0 * (-2.2), degs1);
	Polynom b(monoms);
	a = a * (-2.2);
	EXPECT_EQ(a, b);
}

TEST(Polynom, can_multiply_polynoms) {
	List<Monom> monoms;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 6, 6, 5 };
	const char degs2[3] = { 1, 1, 1 };
	const char degs3[3] = { 1, 2, 2 };
	monoms.push_back(Monom(1.2, degs));
	monoms.push_back(Monom(5.0, degs1));
	Polynom a(monoms);
	monoms[0] = Monom(0.5, degs2);
	monoms[1] = Monom(0.5, degs3);
	Polynom b(monoms);
	ASSERT_NO_THROW(a * b);
}

TEST(Polynom, can_multiply_polynoms_correctly) {
	List<Monom> monoms;
	List<Monom> monoms_res;
	const char degs[3] = { 1, 4, 7 };
	const char degs1[3] = { 6, 6, 5 };
	const char degs2[3] = { 1, 1, 1 };
	const char degs3[3] = { 1, 2, 2 };
	monoms.push_back(Monom(1.2, degs));
	monoms.push_back(Monom(5.0, degs1));
	Polynom a(monoms);
	monoms[0] = Monom(0.5, degs2);
	monoms[1] = Monom(0.5, degs3);
	Polynom b(monoms);
	monoms_res.push_back(Monom(2.5, "\x7\x8\x7"));
	monoms_res.push_back(Monom(2.5, "\x7\x7\x6"));
	monoms_res.push_back(Monom(0.6, "\x2\x6\x9"));
	monoms_res.push_back(Monom(0.6, "\x2\x5\x8"));
	EXPECT_EQ((a * b), Polynom(monoms_res));
}
