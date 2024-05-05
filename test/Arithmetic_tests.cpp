#include <gtest.h>
#include <arithmetic.h>

TEST(TPostfix, can_create)
{
	EXPECT_NO_THROW(TPostfix tmp);
}

TEST(TPostfix, can_insert_polynomial)
{
	TPostfix tmp;
	double arr[8] = { -2, 2, 3, 8, 58, 8, 4, 0 };
	Polynomial p(8, arr);
	EXPECT_NO_THROW(tmp.insert_polynomial("ivanych", p, true));
}

TEST(TPostfix, avail_is_correct)
{
	TPostfix tmp;
	double arr[8] = { 241, 7, 0, 6, 58, 2, 4, 9 };
	Polynomial p(8, arr);
	tmp.insert_polynomial("Abiturient_v_yasli", p, true);
	EXPECT_TRUE(tmp.avail("Abiturient_v_yasli"));
}

TEST(TPostfix, can_search_inserted_polynomial)
{
	TPostfix tmp;
	double arr[8] = { -2, 2, 3, 8, 58, 8, 4, 0 };
	Polynomial p(8, arr);
	tmp.insert_polynomial("Petrovich_1976", p, true);
	EXPECT_NO_THROW(tmp.search("Petrovich_1976"));
}

TEST(TPostfix, insertion_of_a_polynomial_is_correct)
{
	TPostfix tmp;
	double arr[8] = { -2, 2, 3, 8, 58, 8, 4, 0 };
	Polynomial p(8, arr);
	tmp.insert_polynomial("Petrovich_1976", p, true);
	Polynomial t = tmp.search("Petrovich_1976");
	EXPECT_TRUE(p == t);
}

TEST(TPostfix, counts_correctly1)
{
	TPostfix tmp;
	double arr1[12] = { -2, 2, 3, 8, 58, 8, 4, 0, 50, 5, 1, 3 };
	Polynomial p1(12, arr1);
	double arr2[8] = { -15, 5, 1, 3, 2, 2, 3, 8 };
	Polynomial p2(8, arr2);
	tmp.insert_polynomial("Abiturient", p1, true);
	tmp.insert_polynomial("b", p2, true);
	tmp.Polish_Notation("Abiturient+b", false);
	Polynomial p = tmp.count();
	double r[8] = { 35, 5, 1, 3, 58, 8, 4, 0 };
	Polynomial res(8, r);
	EXPECT_TRUE(p == res);
}
