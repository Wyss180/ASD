#include <gtest/gtest.h>
#include "../lib_tree/AVL.h"
#include <string>


TEST(AVLTest, DefaultConstructorCreatesEmptyTree) {
    AVL<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(AVLTest, InsertSingleElement) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_FALSE(tree.is_empty());
}

TEST(AVLTest, InsertMultipleElements) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(7, std::string("seven"));
    EXPECT_FALSE(tree.is_empty());
}

TEST(AVLTest, InsertDuplicateKeyThrows) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_THROW(tree.insert(5, std::string("FIVE")), std::logic_error);
}


TEST(AVLTest, InsertAscendingOrderBalanced) {
    AVL<int, std::string> tree;
    for (int i = 1; i <= 10; ++i) {
        tree.insert(i, std::string("val_") + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), std::string("val_") + std::to_string(i));
    }
}

TEST(AVLTest, InsertDescendingOrderBalanced) {
    AVL<int, std::string> tree;
    for (int i = 10; i >= 1; --i) {
        tree.insert(i, std::string("val_") + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), std::string("val_") + std::to_string(i));
    }
}

TEST(AVLTest, InsertRandomOrder) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(7, std::string("seven"));
    tree.insert(2, std::string("two"));
    tree.insert(4, std::string("four"));
    tree.insert(6, std::string("six"));
    tree.insert(8, std::string("eight"));
    EXPECT_EQ(tree.find(4), std::string("four"));
    EXPECT_EQ(tree.find(6), std::string("six"));
}


TEST(AVLTest, LeftLeftRotation) {
    AVL<int, std::string> tree;
    tree.insert(3, std::string("three"));
    tree.insert(2, std::string("two"));
    tree.insert(1, std::string("one"));
    EXPECT_EQ(tree.find(2), std::string("two"));
    EXPECT_EQ(tree.find(1), std::string("one"));
    EXPECT_EQ(tree.find(3), std::string("three"));
}

TEST(AVLTest, RightRightRotation) {
    AVL<int, std::string> tree;
    tree.insert(1, std::string("one"));
    tree.insert(2, std::string("two"));
    tree.insert(3, std::string("three"));
    EXPECT_EQ(tree.find(2), std::string("two"));
}

TEST(AVLTest, LeftRightRotation) {
    AVL<int, std::string> tree;
    tree.insert(3, std::string("three"));
    tree.insert(1, std::string("one"));
    tree.insert(2, std::string("two"));
    EXPECT_EQ(tree.find(2), std::string("two"));
}

TEST(AVLTest, RightLeftRotation) {
    AVL<int, std::string> tree;
    tree.insert(1, std::string("one"));
    tree.insert(3, std::string("three"));
    tree.insert(2, std::string("two"));
    EXPECT_EQ(tree.find(2), std::string("two"));
}


TEST(AVLTest, FindExistingElement) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_EQ(tree.find(5), std::string("five"));
}

TEST(AVLTest, FindRoot) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    EXPECT_EQ(tree.find(5), std::string("five"));
}

TEST(AVLTest, FindLeftChild) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    EXPECT_EQ(tree.find(3), std::string("three"));
}

TEST(AVLTest, FindRightChild) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(7, std::string("seven"));
    EXPECT_EQ(tree.find(7), std::string("seven"));
}

TEST(AVLTest, FindNonexistentKeyThrows) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_THROW(tree.find(99), std::logic_error);
}

TEST(AVLTest, FindInEmptyTreeThrows) {
    AVL<int, std::string> tree;
    EXPECT_THROW(tree.find(1), std::logic_error);
}


TEST(AVLTest, EraseSingleElement) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.erase(5);
    EXPECT_TRUE(tree.is_empty());
}

TEST(AVLTest, EraseLeaf) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_EQ(tree.find(5), std::string("five"));
}

TEST(AVLTest, EraseNodeWithOneChild) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(2, std::string("two"));
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_EQ(tree.find(2), std::string("two"));
    EXPECT_EQ(tree.find(5), std::string("five"));
}

TEST(AVLTest, EraseNodeWithTwoChildren) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(7, std::string("seven"));
    tree.insert(6, std::string("six"));
    tree.insert(8, std::string("eight"));
    tree.erase(7);
    EXPECT_THROW(tree.find(7), std::logic_error);
    EXPECT_EQ(tree.find(6), std::string("six"));
    EXPECT_EQ(tree.find(8), std::string("eight"));
    EXPECT_EQ(tree.find(5), std::string("five"));
}

TEST(AVLTest, EraseRoot) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(7, std::string("seven"));
    tree.erase(5);
    EXPECT_THROW(tree.find(5), std::logic_error);
    EXPECT_EQ(tree.find(3), std::string("three"));
    EXPECT_EQ(tree.find(7), std::string("seven"));
}

TEST(AVLTest, EraseNonexistentKeyThrows) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_THROW(tree.erase(99), std::logic_error);
}

TEST(AVLTest, EraseFromEmptyThrows) {
    AVL<int, std::string> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

TEST(AVLTest, EraseAndReinsert) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.erase(5);
    tree.insert(5, std::string("FIVE"));
    EXPECT_EQ(tree.find(5), std::string("FIVE"));
}


TEST(AVLTest, ToStringEmpty) {
    AVL<int, std::string> tree;
    EXPECT_TRUE(tree.to_string().empty());
}

TEST(AVLTest, ToStringSingle) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    EXPECT_TRUE(tree.to_string().find("5:five") != std::string::npos);
}

TEST(AVLTest, ToStringSortedOrder) {
    AVL<int, std::string> tree;
    tree.insert(5, std::string("five"));
    tree.insert(3, std::string("three"));
    tree.insert(7, std::string("seven"));
    std::string sorted = tree.to_string_sorted();
    size_t pos3 = sorted.find("3:three");
    size_t pos5 = sorted.find("5:five");
    size_t pos7 = sorted.find("7:seven");
    EXPECT_TRUE(pos3 < pos5 && pos5 < pos7);
}


TEST(AVLTest, MassInsertAndErase) {
    AVL<int, std::string> tree;
    const int N = 500;
    for (int i = 0; i < N; ++i) {
        tree.insert(i, std::string("val_") + std::to_string(i));
    }
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(tree.find(i), std::string("val_") + std::to_string(i));
    }
    for (int i = 0; i < N; i += 2) {
        tree.erase(i);
    }
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0)
            EXPECT_THROW(tree.find(i), std::logic_error);
        else
            EXPECT_EQ(tree.find(i), std::string("val_") + std::to_string(i));
    }
}


TEST(AVLTypes, StringKeyIntValue) {
    AVL<std::string, int> tree;
    tree.insert(std::string("apple"), 1);
    EXPECT_EQ(tree.find(std::string("apple")), 1);
}

TEST(AVLTypes, DoubleKeyStringValue) {
    AVL<double, std::string> tree;
    tree.insert(3.14, std::string("pi"));
    EXPECT_EQ(tree.find(3.14), std::string("pi"));
}