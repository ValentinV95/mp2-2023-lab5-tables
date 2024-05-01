#include "gtest.h"
#include "UnorderedTable.h"
#include "Polynom.h"
#include <string>


TEST(UnorderedTable, can_add_an_element) {
	UnorderedTable<std::string, Polynom> T;
	ASSERT_NO_THROW(T.add("pol1", Polynom("1+x")));
}

TEST(UnorderedTable, can_find_an_element_in_table) {
	UnorderedTable<std::string, Polynom> T;
	T.add("pol1", Polynom("1+x"));
	ASSERT_NO_THROW(T.find("pol1"));
}

TEST(UnorderedTable, throws_when_cant_find_an_element) {
	UnorderedTable<std::string, Polynom> T;
	ASSERT_ANY_THROW(T.find("pol1"));
}

TEST(UnorderedTable, find_is_correct) {
	UnorderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	EXPECT_EQ(p, T.find("pol1"));
}

TEST(UnorderedTable, can_delete) {
	UnorderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	ASSERT_NO_THROW(T.del("pol1"));
}

TEST(UnorderedTable, delete_is_correct) {
	UnorderedTable<std::string, Polynom> T;
	Polynom p = Polynom("1+x");
	T.add("pol1", p);
	T.del("pol1");
	ASSERT_ANY_THROW(T.find("pol1"));
}