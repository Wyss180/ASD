#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

TEST(DSUTest, Find) {
    DSU dsu(5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(DSUTest, FindMultipleCalls) {
    DSU dsu(3);

    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_EQ(dsu.find(1), 1);
}

TEST(DSUTest, SelfUnionDoesNothing) {
    DSU dsu(3);
    dsu.unionSets(1, 1);

    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_EQ(dsu.find(2), 2);
}

TEST(DSUTest, RankDependsOnUnionOrder) {
    DSU dsu1(4);
    DSU dsu2(4);

    dsu1.unionSets(0, 1);
    dsu1.unionSets(2, 3);
    dsu1.unionSets(0, 2);

    dsu2.unionSets(0, 1);
    dsu2.unionSets(1, 2);
    dsu2.unionSets(2, 3);

    EXPECT_NE(dsu1.rank(0), dsu2.rank(0));

    EXPECT_GT(dsu1.rank(0), dsu2.rank(0));
}