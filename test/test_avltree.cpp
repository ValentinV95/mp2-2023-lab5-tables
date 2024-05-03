#include <gtest.h>
#include "avltree.hpp"

TEST(AVLTree, can_remove) {
	AVLTree<int, std::string> tree;
	tree.insert(1, "2");
	ASSERT_NO_THROW(tree.remove(1));
}

TEST(AVLTree, can_insert) {
	AVLTree<int, std::string> tree;
	ASSERT_NO_THROW(tree.insert(1, "2"));
}

TEST(AVLTree, can_find) {
	AVLTree<int, std::string> tree;
	tree.insert(1, "2");
	ASSERT_NO_THROW(tree.find(1));
}

TEST(AVLTree, can_delete) {
	AVLTree<int, std::string>* tree = new AVLTree<int, std::string>();
	tree->insert(1, "text");
	tree->insert(2, "text2");
	tree->insert(6, "text3");
	ASSERT_NO_THROW(delete tree);
}