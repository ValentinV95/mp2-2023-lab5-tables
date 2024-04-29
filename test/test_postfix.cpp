#include <gtest.h>
#include "postfix.h"
#include "polynoms.h"

TEST(Postfix, can_create_postfix)
{
	ASSERT_NO_THROW(Postfix p);
}

TEST(Postfix, can_use_postfix)
{
	Postfix p;
	ASSERT_NO_THROW(p.evaluate("(x-1)*(x+2)+x^2-4x+3"));
}

TEST(Postfix, can_add_variables)
{
	Postfix p;
	ASSERT_NO_THROW(p.insert("var1", { "x^2+4x+4" }, 2));
}

TEST(Postfix, can_use_variables)
{
	Postfix p;
	Polynom pl("x^2-1");
	p.insert("var1", { "x-1" }, 2);
	p.insert("var2", { "x+1" }, 3);
	EXPECT_EQ(pl, p.evaluate("var1*var2"));
}

TEST(Postfix, checks_variable_name_validity)
{
	Postfix p;
	ASSERT_ANY_THROW(p.insert("1var", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("x+y", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("x^2", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("x", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("xyz", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("-x", { "x-1" }, 0));
	ASSERT_ANY_THROW(p.insert("my-var", { "x-1" }, 0));
}

TEST(Postfix, can_remove_variables)
{
	Postfix p;
	p.insert("var", { "x" }, 3);
	p.remove("var", 3);
	ASSERT_ANY_THROW(p.evaluate("var"));
}

TEST(Postfix, misplaced_parenthesis)
{
	Postfix p;
	ASSERT_ANY_THROW(p.evaluate("x+(3"));
	ASSERT_ANY_THROW(p.evaluate("x+3)"));
	ASSERT_ANY_THROW(p.evaluate("()"));
	ASSERT_ANY_THROW(p.evaluate("x+)("));
	ASSERT_ANY_THROW(p.evaluate("(x+1))"));
	ASSERT_ANY_THROW(p.evaluate("((x+1)"));
}

TEST(Postfix, can_use_exp_notation)
{
	Postfix p;
	ASSERT_NO_THROW(p.evaluate("1e+09x"));
	ASSERT_NO_THROW(p.evaluate("1.44e+09x"));
}

TEST(Postfix, can_use_complex_expressions)
{
	Postfix p;
	Polynom pl("1e+09");
	p.insert("var", { "10x-9" }, 2);
	EXPECT_EQ(pl, p.evaluate("var - 5*(x+4)*(x-2)-31+5x^2+1e+09"));
}