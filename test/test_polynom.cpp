#include "polynoms.h"
#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynom p);
}

TEST(Polynom, can_copy_polynom)
{
	Polynom p1;
	ASSERT_NO_THROW(Polynom p2(p1));
}

TEST(Polynom, copied_polynoms_are_equal)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1);
	p1.insertMonom(1, 0, 1, 1);
	p1.insertMonom(0, 1, 1, 1);
	p1.insertMonom(0, 0, 1, 1);
	Polynom p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(Polynom, can_assing_polynom)
{
	Polynom p1;
	Polynom p2;
	ASSERT_NO_THROW(p2 = p1);
}

TEST(Polynom, assigned_polynoms_are_equal)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 2.5);
	p1.insertMonom(0, 0, 3, 2.0);
	Polynom p2;
	p2.insertMonom(1, 0, 0, 10.0);
	p2.insertMonom(1, 2, 3, 15.0);
	p2.insertMonom(7, 2, 3, 15.0);
	p2 = p1;
	EXPECT_EQ(p2, p1);
}

TEST(Polynom, can_insert_monom)
{
	Polynom p;
	ASSERT_NO_THROW(p.insertMonom(1, 1, 1, 1));
}

TEST(Polynom, can_stack_coefs_with_monom_insertion)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	p1.insertMonom(1, 1, 1, 1.0);

	Polynom p2;
	p2.insertMonom(1, 1, 1, 2.0);

	EXPECT_EQ(p1, p2);
}

TEST(Polynom, can_get_zero_polynom_with_monom_insertion)
{
	Polynom p1;
	Polynom p2;

	p1.insertMonom(1, 1, 1, 1.0);
	p1.insertMonom(1, 1, 1, -1.0);

	EXPECT_EQ(p1, p2);
}

TEST(Polynom, throws_when_monom_degree_is_too_big)
{
	Polynom p;
	ASSERT_ANY_THROW(p.insertMonom(MAX_MONOM_DEGREE, 0, 0, 0));
	ASSERT_ANY_THROW(p.insertMonom(0, MAX_MONOM_DEGREE, 0, 0));
	ASSERT_ANY_THROW(p.insertMonom(0, 0, MAX_MONOM_DEGREE, 0));
}

TEST(Polynom, can_print_polynom)
{
	Polynom p;
	p.insertMonom(2, 0, 0, 1.0);
	p.insertMonom(1, 0, 0, 2.0);
	p.insertMonom(1, 1, 1, -3.5);
	p.insertMonom(1, 1, 0, 1.0);
	p.insertMonom(0, 1, 1, 3.5);
	EXPECT_EQ("-3.5xyz+x^2+xy+3.5yz+2x", p.getString());
}

TEST(Polynom, can_print_zero_polynom)
{
	Polynom p;
	EXPECT_EQ("0", p.getString());
}

TEST(Polynom, can_print_constant)
{
	Polynom p;
	p.insertMonom(0, 0, 0, 42.0);
	EXPECT_EQ("42", p.getString());
}

TEST(Polynom, can_print_polynom_with_first_positive)
{
	Polynom p;
	p.insertMonom(2, 0, 0, 2.0);
	p.insertMonom(1, 0, 0, 1.0);
	EXPECT_EQ("2x^2+x", p.getString());
}

TEST(Polynom, can_print_polynom_with_unit_coefficient)
{
	Polynom p1, p2;
	p1.insertMonom(2, 0, 0, 1.0);
	p2.insertMonom(2, 0, 0, -1.0);
	ASSERT_EQ("x^2", p1.getString());
	ASSERT_EQ("-x^2", p2.getString());
}

TEST(Polynom, zero_polynoms_are_equal)
{
	Polynom p1;
	Polynom p2;
	EXPECT_EQ(p1, p2);
}

TEST(Polynom, can_add_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 0, 0, 2.0);
	p1.insertMonom(0, 1, 0, 7.0);
	p1.insertMonom(0, 1, 2, -1.0);
	p1.insertMonom(0, 0, 4, -1.0);

	Polynom p2;
	p2.insertMonom(1, 0, 0, 3.0);
	p2.insertMonom(1, 0, 1, 1.0);
	p2.insertMonom(5, 0, 5, 2.0);
	p2.insertMonom(0, 0, 4, 1.0);

	Polynom p3;
	p3.insertMonom(1, 0, 0, 2.0);
	p3.insertMonom(0, 1, 0, 7.0);
	p3.insertMonom(0, 1, 2, -1.0);
	p3.insertMonom(0, 0, 4, -1.0);
	p3.insertMonom(1, 0, 0, 3.0);
	p3.insertMonom(1, 0, 1, 1.0);
	p3.insertMonom(5, 0, 5, 2.0);
	p3.insertMonom(0, 0, 4, 1.0);

	ASSERT_EQ(p3, p1 + p2);
	ASSERT_EQ(p3, p2 + p1);
}

TEST(Polynom, can_get_zero_polynom_after_addition)
{
	Polynom p1;
	p1.insertMonom(1, 0, 0, 1.0);

	Polynom p2;
	p2.insertMonom(1, 0, 0, -1.0);

	Polynom p3;
	ASSERT_EQ(p3, p1 + p2);
	ASSERT_EQ(p3, p2 + p1);
}

TEST(Polynom, can_subtract_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 0, 0, 2.0);

	Polynom p2;
	p2.insertMonom(1, 0, 0, 3.0);
	p2.insertMonom(1, 0, 1, 1.0);

	Polynom p3;
	p3.insertMonom(1, 0, 0, -1.0);
	p3.insertMonom(1, 0, 1, -1.0);

	EXPECT_EQ(p3, p1 - p2);
}

TEST(Polynom, can_get_zero_polynom_after_subtraction)
{
	Polynom p1;
	p1.insertMonom(1, 0, 0, 1.0);

	Polynom p2;
	p2.insertMonom(1, 0, 0, 1.0);

	Polynom p3;
	EXPECT_EQ(p3, p1 - p2);
}

TEST(Polynom, can_multiply_polynoms)
{
	Polynom p1;
	p1.insertMonom(2, 0, 0, 1.0);
	p1.insertMonom(1, 1, 0, 2.0);
	p1.insertMonom(0, 2, 0, -1.0);
	p1.insertMonom(0, 1, 0, 3.0);

	Polynom p2;
	p2.insertMonom(1, 0, 0, 1.0);
	p2.insertMonom(0, 3, 0, 1.0);
	p2.insertMonom(1, 1, 1, 1.0);

	Polynom p3;
	p3.insertMonom(3, 1, 1, 1.0);
	p3.insertMonom(3, 0, 0, 1.0);
	p3.insertMonom(2, 3, 0, 1.0);
	p3.insertMonom(2, 2, 1, 2.0);
	p3.insertMonom(2, 1, 0, 2.0);
	p3.insertMonom(1, 4, 0, 2.0);
	p3.insertMonom(1, 3, 1, -1.0);
	p3.insertMonom(1, 2, 1, 3.0);
	p3.insertMonom(1, 2, 0, -1.0);
	p3.insertMonom(1, 1, 0, 3.0);
	p3.insertMonom(0, 5, 0, -1.0);
	p3.insertMonom(0, 4, 0, 3.0);

	ASSERT_EQ(p3, p1 * p2);
	ASSERT_EQ(p3, p2 * p1); 
}

TEST(Polynom, can_get_zero_polynom_after_multiplication)
{
	Polynom p1;
	p1.insertMonom(2, 2, 2, 2.0);
	p1.insertMonom(1, 0, 0, 1.0);

	Polynom p2;
	Polynom p3;
	EXPECT_EQ(p3, p1 * p2);
}

TEST(Polynom, throws_when_gets_monom_with_too_high_deg_in_multiplication)
{
	Polynom p1;
	p1.insertMonom(MAX_MONOM_DEGREE - 2, MAX_MONOM_DEGREE - 2, MAX_MONOM_DEGREE - 2, 4.0);

	Polynom p2;
	p2.insertMonom(3, 3, 3, 4.0);

	ASSERT_ANY_THROW(p1 * p2);
}

TEST(Polynom, can_multiply_on_constant)
{
	double c = 3.0;

	Polynom p1;
	p1.insertMonom(1, 1, 1, 3.0);
	p1.insertMonom(1, 1, 0, 2.0);
	p1.insertMonom(1, 0, 0, 1.0);

	Polynom p2;
	p2.insertMonom(1, 1, 1, c * 3.0);
	p2.insertMonom(1, 1, 0, c * 2.0);
	p2.insertMonom(1, 0, 0, c * 1.0);

	EXPECT_EQ(p2, p1 * c);
}

TEST(Polynom, can_get_zero_polynom_after_multiplication_on_constant)
{
	Polynom p1;
	p1.insertMonom(1, 0, 0, 42.0);

	Polynom p2;

	EXPECT_EQ(p2, p1 * 0);
}

TEST(Polynom, equality_returns_true_on_equal_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 1.0);
	EXPECT_TRUE(p1 == p2);
}

TEST(Polynom, equality_returns_false_on_unequal_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 2.0);
	EXPECT_FALSE(p1 == p2);
}

TEST(Polynom, equality_returns_false_when_polynoms_have_different_size)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 2.0);
	p2.insertMonom(1, 2, 1, 2.0);
	EXPECT_FALSE(p1 == p2);
}

TEST(Polynom, inequality_returns_false_on_equal_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 1.0);
	EXPECT_FALSE(p1 != p2);
}

TEST(Polynom, inequality_returns_true_on_unequal_polynoms)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 2.0);
	EXPECT_TRUE(p1 != p2);
}

TEST(Polynom, inequality_returns_true_when_polynoms_have_different_size)
{
	Polynom p1;
	p1.insertMonom(1, 1, 1, 1.0);
	Polynom p2;
	p2.insertMonom(1, 1, 1, 2.0);
	p2.insertMonom(1, 2, 1, 2.0);
	EXPECT_TRUE(p1 != p2);
}