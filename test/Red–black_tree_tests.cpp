#include <gtest.h>
#include <RBT.h>

TEST(UV_RBT, can_create)
{
	using table = UV_RBT<string, int>;
	EXPECT_NO_THROW(table tmp);
}

TEST(UV_RBT, can_insert)
{
	UV_RBT<string, int> tmp;
	EXPECT_NO_THROW(tmp.insert("vasya", 2));
	EXPECT_NO_THROW(tmp.insert("baton", 1243621));
}
	
TEST(UV_RBT, can_search)
{
	UV_RBT<string, int> tmp;
	tmp.insert("vasya", 2);
	tmp.insert("baton", 1243621);
	EXPECT_NO_THROW(tmp.search("vasya"));
	EXPECT_NO_THROW(tmp.search("baton"));
}

TEST(UV_RBT, search_and_insert_is_correct)
{
	UV_RBT<string, int> tmp;
	tmp.insert("vasya", 2);
	tmp.insert("baton", 1243621);
	EXPECT_EQ(tmp.search("vasya"), 2);
	EXPECT_EQ(tmp.search("baton"), 1243621);
}

TEST(UV_RBT, can_avail)
{
	UV_RBT<string, int> tmp;
	tmp.insert("vasya", 2);
	tmp.insert("baton", 1243621);
	EXPECT_NO_THROW(tmp.avail("vasya"));
	EXPECT_NO_THROW(tmp.avail("baton"));
}

TEST(UV_RBT, avail_is_correct)
{
	UV_RBT<string, int> tmp;
	tmp.insert("vasya", 2);
	tmp.insert("baton", 1243621);
	EXPECT_TRUE(tmp.avail("vasya"));
	EXPECT_TRUE(tmp.avail("baton"));
}

TEST(UV_RBT, can_delete)
{
	UV_RBT<string, int> tmp;
	tmp.insert("baton", 1243621);
	EXPECT_NO_THROW(tmp.del("baton"));
}

TEST(UV_RBT, delete_is_correct)
{
	UV_RBT<string, int> tmp;
	tmp.insert("baton", 1243621);
	tmp.del("baton");
	EXPECT_FALSE(tmp.avail("baton"));
}