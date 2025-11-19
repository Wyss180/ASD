#include <gtest/gtest.h>
#include "../lib_list/list.h"
#include "../lib_algorithms/algorithms.h"
#include "../lib_algorithms/algorithms.cpp"



TEST(CheckBracketsTest, empty_string) {
    EXPECT_TRUE(check_breckets(""));
}

TEST(CheckBracketsTest, simple_correct_pairs) {
    EXPECT_TRUE(check_breckets("()"));
    EXPECT_TRUE(check_breckets("[]"));
    EXPECT_TRUE(check_breckets("{}"));
}

TEST(CheckBracketsTest, nested_correct) {
    EXPECT_TRUE(check_breckets("({[]})"));
    EXPECT_TRUE(check_breckets("()[]{}"));
    EXPECT_TRUE(check_breckets("{[()]}"));
}

TEST(CheckBracketsTest, unmatched_opening) {
    EXPECT_FALSE(check_breckets("("));
    EXPECT_FALSE(check_breckets("["));
    EXPECT_FALSE(check_breckets("{"));
    EXPECT_FALSE(check_breckets("({"));
}

TEST(CheckBracketsTest, unmatched_closing) {
    EXPECT_FALSE(check_breckets(")"));
    EXPECT_FALSE(check_breckets("]"));
    EXPECT_FALSE(check_breckets("}"));
    EXPECT_FALSE(check_breckets("())"));
}

TEST(CheckBracketsTest, wrong_order) {
    EXPECT_FALSE(check_breckets("([)]"));
    EXPECT_FALSE(check_breckets("{(})"));
    EXPECT_FALSE(check_breckets("]["));
}

TEST(CheckBracketsTest, wrong_pairs) {
    EXPECT_FALSE(check_breckets("(]"));
    EXPECT_FALSE(check_breckets("{)"));
    EXPECT_FALSE(check_breckets("[}"));
}

TEST(CheckBracketsTest, invalid_characters) {
    EXPECT_FALSE(check_breckets("a"));
    EXPECT_FALSE(check_breckets("(a)"));
    EXPECT_FALSE(check_breckets("1"));
    EXPECT_FALSE(check_breckets("()a"));
}

TEST(CycleTest, RealExample1_CycleInMiddle) {
    Node<int>* node1 = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);
    Node<int>* node4 = new Node<int>(4);
    Node<int>* node5 = new Node<int>(5);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node3;

    EXPECT_TRUE(cycle(node1));

    node5->next = nullptr;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(CycleTest, RealExample2_NoCycle) {
    Node<int>* node1 = new Node<int>(10);
    Node<int>* node2 = new Node<int>(20);
    Node<int>* node3 = new Node<int>(30);
    Node<int>* node4 = new Node<int>(40);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    EXPECT_FALSE(cycle(node1));

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}