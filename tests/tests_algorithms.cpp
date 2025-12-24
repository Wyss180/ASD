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

TEST(IslandsEdgeCases, EmptyMatrix) {
    std::vector<std::vector<int>> empty;
    EXPECT_EQ(count_islands(empty), 0);
}

TEST(IslandsEdgeCases, MatrixWithEmptyRow) {
    std::vector<std::vector<int>> matrix = { {} };
    EXPECT_EQ(count_islands(matrix), 0);
}

TEST(IslandsEdgeCases, SingleCellZero) {
    std::vector<std::vector<int>> matrix = { {0} };
    EXPECT_EQ(count_islands(matrix), 0);
}

TEST(IslandsEdgeCases, SingleCellOne) {
    std::vector<std::vector<int>> matrix = { {1} };
    EXPECT_EQ(count_islands(matrix), 1);
}

TEST(IslandsEdgeCases, AllZeros) {
    std::vector<std::vector<int>> matrix = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    EXPECT_EQ(count_islands(matrix), 0);
}

TEST(IslandsEdgeCases, AllOnesLarge) {
    std::vector<std::vector<int>> matrix = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
    EXPECT_EQ(count_islands(matrix), 1);
}

TEST(IslandsEdgeCases, OnlyFirstRow) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    EXPECT_EQ(count_islands(matrix), 3);
}

TEST(IslandsEdgeCases, OnlyFirstColumn) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 0},
        {1, 0, 0},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 0}
    };
    EXPECT_EQ(count_islands(matrix), 2);
}

TEST(IslandsEdgeCases, LastRowConnection) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 1}
    };
    EXPECT_EQ(count_islands(matrix), 4);
}

TEST(IslandsEdgeCases, ChessBoardPattern) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    EXPECT_EQ(count_islands(matrix), 8);
}

TEST(IslandsEdgeCases, SnakePattern) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1}
    };
    EXPECT_EQ(count_islands(matrix), 1);
}


TEST(IslandsEdgeCases, DiamondShape) {
    std::vector<std::vector<int>> matrix = {
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0}
    };
    EXPECT_EQ(count_islands(matrix), 8);
}

TEST(IslandsEdgeCases, ChainReactionUnions) {
    std::vector<std::vector<int>> matrix = {
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1}
    };
    EXPECT_EQ(count_islands(matrix), 1);
}

TEST(IslandsEdgeCases, IrregularMatrix) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1},
        {0, 1},
        {1, 0, 1, 0}
    };
    EXPECT_NO_THROW(count_islands(matrix));
}

TEST(IslandsEdgeCases, RealisticMap) {
    std::vector<std::vector<int>> matrix = {
        {1, 1, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 1},
        {0, 1, 0, 0, 0, 1, 1}
    };
    EXPECT_EQ(count_islands(matrix), 10);
}

TEST(CycleDetection, EmptyList) {
    EXPECT_FALSE(hasCycle<int>(nullptr));
    EXPECT_FALSE(hasCycleReverse<int>(nullptr));
}

TEST(CycleDetection, SimpleNoCycle) {
    Node<int> node1(1);
    Node<int> node2(2);
    Node<int> node3(3);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = nullptr;

    EXPECT_FALSE(hasCycle(&node1));
    EXPECT_FALSE(hasCycleReverse(&node1));
}

TEST(CycleDetection, SimpleCycle) {
    Node<int> node1(1);
    Node<int> node2(2);
    Node<int> node3(3);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node2; 

    EXPECT_TRUE(hasCycle(&node1));
    EXPECT_TRUE(hasCycleReverse(&node1));
}

TEST(CycleDetection, SelfCycle) {
    Node<int> node1(1);
    node1.next = &node1; 

    EXPECT_TRUE(hasCycle(&node1));
    EXPECT_TRUE(hasCycleReverse(&node1));
}

TEST(CycleDetection, TwoNodesCycle) {
    Node<int> node1(1);
    Node<int> node2(2);

    node1.next = &node2;
    node2.next = &node1;

    EXPECT_TRUE(hasCycle(&node1));
    EXPECT_TRUE(hasCycleReverse(&node1));
}