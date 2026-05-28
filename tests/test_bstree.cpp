#include <gtest/gtest.h>
#include "../lib_tree/BSTree.h"
using namespace std::string_literals;


TEST(BSTreeTest, EraseLeaf) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, EraseNodeWithLeftChild) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(2, "two");
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_EQ(tree.find(2), "two");
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, EraseNodeWithRightChild) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_EQ(tree.find(4), "four");
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, EraseNodeWithTwoChildren) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(6, "six");
    tree.insert(8, "eight");
    tree.erase(7);
    EXPECT_THROW(tree.find(7), std::logic_error);
    EXPECT_EQ(tree.find(6), "six");
    EXPECT_EQ(tree.find(8), "eight");
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, EraseRoot) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.erase(5);
    EXPECT_THROW(tree.find(5), std::logic_error);
    EXPECT_TRUE(tree.find(3) == "three");
    EXPECT_TRUE(tree.find(7) == "seven");
}

TEST(BSTreeTest, InsertAndEraseSequence) {
    BSTree<int, std::string> tree;
    for (int i = 0; i < 20; ++i) {
        tree.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 0; i < 20; i += 2) {
        tree.erase(i);
    }
    for (int i = 0; i < 20; ++i) {
        if (i % 2 == 0)
            EXPECT_THROW(tree.find(i), std::logic_error);
        else
            EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
    }
}