// тесты для вычисления арифметических выражений

#include "arithmetic.hpp"
#include <gtest.h>
#include <iostream>

TEST(TPostfix, can_do_simple_operations) {
	EXPECT_NEAR(-4.0, calculate_expr("-4"), 1e-5);
	EXPECT_NEAR(4.0, calculate_expr("2+2"), 1e-5);
	EXPECT_NEAR(2.0, calculate_expr("4-2"), 1e-5);
	EXPECT_NEAR(6.0, calculate_expr("2*3"), 1e-5);
	EXPECT_NEAR(0.33333333, calculate_expr("1/3"), 1e-5);
}

TEST(TPostfix, can_do_complex_operations) {
	std::istringstream test("1 2 3 4 5");
	EXPECT_NEAR(sin(1), calculate_expr("sin(x1)", test), 1e-5);
	EXPECT_NEAR(cos(2), calculate_expr("cos(x2)", test), 1e-5);
	EXPECT_NEAR(tan(3), calculate_expr("tan(x3)", test), 1e-5);
	EXPECT_NEAR(exp(4), calculate_expr("exp(x4)", test), 1e-5);
	EXPECT_NEAR(log10(5), calculate_expr("lg(x5)", test), 1e-5);
}

TEST(TPostfix, throws_when_incorrect_function_usage) {
	ASSERT_ANY_THROW(calculate_expr("func(5)"));
	ASSERT_ANY_THROW(calculate_expr("sin()"));
	ASSERT_ANY_THROW(calculate_expr("sin("));
}

TEST(TPostfix, common_mistakes) {
	ASSERT_ANY_THROW(calculate_expr("1+)2"));
	ASSERT_ANY_THROW(calculate_expr("+sin(2)"));
	ASSERT_ANY_THROW(calculate_expr("()"));
	ASSERT_ANY_THROW(calculate_expr(")"));
	ASSERT_ANY_THROW(calculate_expr("2+*3"));
	ASSERT_ANY_THROW(calculate_expr("1/0"));
}

TEST(TPostfix, input_numbers) {
	EXPECT_NEAR(1.0, calculate_expr("1.0"), 1e-5);
	EXPECT_NEAR(1.2e+6, calculate_expr("1.2e+6"), 1e-5);
	EXPECT_NEAR(1.2e-6, calculate_expr("1.2e-6"), 1e-5);
}
