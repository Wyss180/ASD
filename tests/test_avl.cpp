#include <gtest/gtest.h>
#include "../lib_tree/AVL.h"
#include <string>

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

TEST(AVLBalanceTest, insert10root100to50) {
    AVL<int, std::string> tree;

    tree.insert(100, "hundred");
    tree.insert(50, "fifty");
    tree.insert(150, "one fifty");
    tree.insert(25, "twenty five");
    tree.insert(75, "seventy five");
    tree.insert(175, "one seventy five");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");
    tree.insert(60, "sixty");
    tree.insert(80, "eighty");

    ASSERT_EQ(tree.root(), 100);

    tree.insert(10, "ten");

    EXPECT_EQ(tree.root(), 50);

    for (int k : {10, 20, 25, 30, 50, 60, 75, 80, 100, 150, 175}) {
        EXPECT_NO_THROW(tree.find(k));
    }
}

TEST(AVLDeleteTest, erase25root40to60) {
    AVL<int, std::string> tree;

    tree.insert(40, "forty");
    tree.insert(20, "twenty");
    tree.insert(60, "sixty");
    tree.insert(15, "fifteen");
    tree.insert(25, "twenty five");
    tree.insert(50, "fifty");
    tree.insert(70, "seventy");
    tree.insert(5, "five");
    tree.insert(45, "forty five");
    tree.insert(55, "fifty five");
    tree.insert(65, "sixty five");
    tree.insert(80, "eighty");
    tree.insert(75, "seventy five");

    ASSERT_EQ(tree.root(), 40);

    tree.erase(25);

    EXPECT_EQ(tree.root(), 60);

    EXPECT_THROW(tree.find(25), std::logic_error);

    std::vector<int> remaining = { 5,15,20,40,45,50,55,60,65,70,75,80 };
    for (int k : remaining) {
        EXPECT_NO_THROW(tree.find(k));
    }
}

TEST(AVLtest, insertBalanceRR) {
    AVL<int, int> tree;

    tree.insert(100, 100);
    tree.insert(50, 50);
    tree.insert(25, 25);

    EXPECT_EQ(tree.root(), 50);
}

TEST(AVLtest, insertBalanceLL) {
    AVL<int, int> tree;

    tree.insert(100, 100);
    tree.insert(150, 150);
    tree.insert(175, 175);

    EXPECT_EQ(tree.root(), 150);
}

TEST(AVLtest, insertBalanceLR) {
    AVL<int, int> tree;

    tree.insert(100, 100);
    tree.insert(50, 50);
    tree.insert(75, 75);

    EXPECT_EQ(tree.root(), 75);
}

TEST(AVLtest, insertBalanceRL) {
    AVL<int, int> tree;
    tree.insert(100, 100);
    tree.insert(150, 150);
    tree.insert(125, 125);

    EXPECT_EQ(tree.root(), 125);

}

TEST(AVLtest, eraseSingle) {
    AVL<int, int> tree;

    tree.insert(1,1);
    tree.erase(1);
    EXPECT_TRUE(tree.is_empty());
}