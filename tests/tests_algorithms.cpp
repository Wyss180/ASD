#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"


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