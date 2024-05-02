#include <gtest.h>
#include "Unordered_table.h"

TEST(LR_UnordTable, can_create)
{
	using table = LR_UnordTable<string, int>;
	EXPECT_NO_THROW(table tmp);
}
TEST(LR_UnordTable, can_push)
{
	LR_UnordTable<string, int> tmp;
	EXPECT_NO_THROW(tmp.push("vasya", 2));
	EXPECT_NO_THROW(tmp.push("baton", 1243621));
}
TEST(LR_UnordTable, can_return)
{
	LR_UnordTable<string, int> tmp;
	tmp.push("vasya", 2);
	EXPECT_NO_THROW(tmp.return_by_Ldata("vasya"));
}
TEST(LR_UnordTable, return_is_correct)
{
	LR_UnordTable<string, int> tmp;
	tmp.push("vasya", 2);
	EXPECT_EQ(tmp.return_by_Ldata("vasya"), 2);
}
TEST(LR_UnordTable, can_check_availability)
{
	LR_UnordTable<string, int> tmp;
	tmp.push("vasya", 2);
	EXPECT_TRUE(tmp.is_Ldata("vasya"));
}
TEST(LR_UnordTable, can_delete)
{
	LR_UnordTable<string, int> tmp;
	tmp.push("vasya", 2);
	EXPECT_NO_THROW(tmp.del_by_Ldata("vasya"));
}
TEST(LR_UnordTable, deletes_correctly)
{
	LR_UnordTable<string, int> tmp;
	tmp.push("vasya", 2);
	tmp.del_by_Ldata("vasya");
	EXPECT_FALSE(tmp.is_Ldata("vasya"));
}