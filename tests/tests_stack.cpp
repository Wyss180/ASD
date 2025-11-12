#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(StackTest, create_stack) {
    ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(StackTest, push_and_top) {
    Stack<int> s(5);
    s.push(10);
    s.push(20);

    EXPECT_EQ(s.top(), 20);
}

TEST(StackTest, push_and_pop) {
    Stack<int> s(5);
    s.push(10);
    s.push(20);
    s.push(30);

    EXPECT_EQ(s.top(), 30);
    s.pop();
    EXPECT_EQ(s.top(), 20);
    s.pop();
    EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, check_empty) {
    Stack<int> s(3);
    EXPECT_TRUE(s.isEmpty());

    s.push(1);
    EXPECT_FALSE(s.isEmpty());

    s.pop();
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, check_full) {
    Stack<int> s(2);
    EXPECT_FALSE(s.isFull());

    s.push(1);
    EXPECT_FALSE(s.isFull());

    s.push(2);
    EXPECT_TRUE(s.isFull());
}

TEST(StackTest, throw_when_empty) {
    Stack<int> s(3);
    EXPECT_THROW(s.pop(), std::logic_error);
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(StackTest, throw_when_full) {
    Stack<int> s(2);
    s.push(1);
    s.push(2);

    EXPECT_THROW(s.push(3), std::logic_error);
}

TEST(StackTest, clear_stack) {
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_FALSE(s.isEmpty());
    s.clear();
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, check_size) {
    Stack<int> s(5);
    EXPECT_EQ(s.size(), 0);

    s.push(1);
    EXPECT_EQ(s.size(), 1);

    s.push(2);
    EXPECT_EQ(s.size(), 2);

    s.pop();
    EXPECT_EQ(s.size(), 1);

    s.clear();
    EXPECT_EQ(s.size(), 0);
}