#include <gtest/gtest.h>
#include "../lib_tree/BSTree.h"
using namespace std::string_literals;


TEST(BSTreeTest, DefaultConstructorCreatesEmptyTree) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(BSTreeTest, InsertSingleElement) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
}

TEST(BSTreeTest, InsertDuplicateKeyThrows) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_THROW(tree.insert(5, "FIVE"), std::logic_error);
}

TEST(BSTreeTest, InsertAscendingOrder) {
    BSTree<int, std::string> tree;
    for (int i = 1; i <= 10; ++i) {
        tree.insert(i, "val_" + std::to_string(i));
    }
    EXPECT_FALSE(tree.is_empty());
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
    }
}

TEST(BSTreeTest, InsertDescendingOrder) {
    BSTree<int, std::string> tree;
    for (int i = 10; i >= 1; --i) {
        tree.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
    }
}


TEST(BSTreeTest, FindExistingElement) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, FindNonexistentThrows) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_THROW(tree.find(99), std::logic_error);
}

TEST(BSTreeTest, FindInEmptyTreeThrows) {
    BSTree<int, std::string> tree;
    EXPECT_THROW(tree.find(1), std::logic_error);
}


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

TEST(BSTreeTest, EraseNonexistentThrows) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_THROW(tree.erase(99), std::logic_error);
}

TEST(BSTreeTest, EraseFromEmptyThrows) {
    BSTree<int, std::string> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}


TEST(BSTreeTest, ToStringEmpty) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.to_string().empty());
}

TEST(BSTreeTest, ToStringSingle) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_TRUE(tree.to_string().find("5:five") != std::string::npos);
}

TEST(BSTreeTest, ToStringSortedOrder) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    std::string sorted = tree.to_string_sorted();
    size_t pos3 = sorted.find("3:three");
    size_t pos5 = sorted.find("5:five");
    size_t pos7 = sorted.find("7:seven");
    EXPECT_TRUE(pos3 < pos5 && pos5 < pos7);
}


TEST(BSTreeTypes, StringKeyIntValue) {
    BSTree<std::string, int> tree;
    tree.insert("apple", 1);
    EXPECT_EQ(tree.find("apple"), 1);
}

TEST(BSTreeTypes, DoubleKeyStringValue) {
    BSTree<double, std::string> tree;
    tree.insert(3.14, "pi");
    EXPECT_EQ(tree.find(3.14), "pi");
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