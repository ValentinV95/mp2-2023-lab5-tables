#include <gtest.h>
#include <Hash_table.h>

TEST(Hash, can_create)
{
	using table = Hash<string, int>;
	EXPECT_NO_THROW(table tmp);
}
TEST(Hash, can_push)
{
	Hash<string, int> tmp;
	EXPECT_NO_THROW(tmp.push("Valera", 97));
	EXPECT_NO_THROW(tmp.push("zykhra", 654456));
}
TEST(Hash, can_delete)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	EXPECT_NO_THROW(tmp.del("Valera"));
	EXPECT_NO_THROW(tmp.del("zykhra"));
}
TEST(Hash, can_find)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	EXPECT_NO_THROW(tmp.find("Valera"));
	EXPECT_NO_THROW(tmp.find("zykhra"));
}
TEST(Hash, finds_correctly)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	EXPECT_EQ(tmp.find("Valera"),97);
	EXPECT_EQ(tmp.find("zykhra"), 654456);
}
TEST(Hash, can_avail)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	EXPECT_NO_THROW(tmp.find("Valera"));
	EXPECT_NO_THROW(tmp.find("zykhra"));
}
TEST(Hash, avails_correctly)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	EXPECT_TRUE(tmp.avail("Valera"));
	EXPECT_TRUE(tmp.avail("zykhra"));
}
TEST(Hash, deletes_correctly)
{
	Hash<string, int> tmp;
	tmp.push("Valera", 97);
	tmp.push("zykhra", 654456);
	tmp.del("Valera");
	tmp.del("zykhra");
	EXPECT_FALSE(tmp.avail("Valera"));
	EXPECT_FALSE(tmp.avail("zykhra"));
}
