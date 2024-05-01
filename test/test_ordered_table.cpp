#include "gtest.h"
#include "OrderedTable.h"
#include "Polynom.h"
#include <string>

TEST(OrderedTable, can_add_an_element) {
	OrderedTable<std::string, Polynom> T;
	ASSERT_NO_THROW(T.add("pol1", Polynom("1+x")));
}

TEST(OrderedTable, can_find_an_element_in_table) {
	OrderedTable<std::string, Polynom> T;
	T.add("pol1", Polynom("1+x"));
	ASSERT_NO_THROW(T.find("pol1"));
}

TEST(OrderedTable, throws_when_cant_find_an_element) {
	OrderedTable<std::string, Polynom> T;
	ASSERT_ANY_THROW(T.find("pol1"));
}

TEST(OrderedTable, find_is_correct) {
	OrderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	EXPECT_EQ(p, T.find("pol1"));
}

TEST(OrderedTable, can_delete) {
	OrderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	ASSERT_NO_THROW(T.del("pol1"));
}

TEST(OrderedTable, delete_is_correct) {
	OrderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	T.del("pol1");
	ASSERT_ANY_THROW(T.find("pol1"));
}