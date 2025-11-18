#include <gtest/gtest.h>
#include "../lib_Tstack/Tstack.h"
#include "../lib_list/list.h"

TEST(TStackTest, Empty) {
    TStack<int> s;
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.size(), 0);
}

TEST(TStackTest, PushPop) {
    TStack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(TStackTest, Overflow) {
    TStack<int> s(2);
    s.push(1);
    s.push(2);
    EXPECT_THROW(s.push(3), std::logic_error);
}

TEST(TStackTest, Underflow) {
    TStack<int> s;
    EXPECT_THROW(s.pop(), std::logic_error);
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(TStackTest, Clear) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    EXPECT_TRUE(s.isEmpty());
}