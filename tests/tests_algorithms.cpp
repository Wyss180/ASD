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

TEST(IslandsTest, EmptyGrid) {
    std::vector<std::vector<int>> empty_grid;
    EXPECT_EQ(count_islands(empty_grid), 0);
}

TEST(IslandsTest, GridWithZeroRows) {
    std::vector<std::vector<int>> grid(0, std::vector<int>(5));
    EXPECT_EQ(count_islands(grid), 0);
}

TEST(IslandsTest, GridWithZeroCols) {
    std::vector<std::vector<int>> grid = { {}, {}, {} };
    EXPECT_EQ(count_islands(grid), 0);
}

TEST(IslandsTest, AllZeros) {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    EXPECT_EQ(count_islands(grid), 0);
}

TEST(IslandsTest, AllOnesSingleIsland) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    EXPECT_EQ(count_islands(grid), 1);
}

TEST(IslandsTest, SingleIslandCenter) {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    EXPECT_EQ(count_islands(grid), 1);
}

TEST(IslandsTest, MultipleSeparateIslands) {
    std::vector<std::vector<int>> grid = {
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };
    EXPECT_EQ(count_islands(grid), 9);
}

TEST(IslandsTest, ThreeDifferentIslands) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 1}
    };
    EXPECT_EQ(count_islands(grid), 5);
}

TEST(IslandsTest, LaterConnectedIslands) {
    std::vector<std::vector<int>> grid = {
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0}
    };
    EXPECT_EQ(count_islands(grid), 5);
}

