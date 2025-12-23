#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

TEST(DSUTest, Find) {
    DSU dsu(5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
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

TEST(DSUTest, FindAndUnion) {
    DSU dsu(12);

    for (int cluster = 0; cluster < 3; cluster++) {
        int base = cluster * 4;
        dsu.unionSets(base, base + 1);
        dsu.unionSets(base + 2, base + 3);
        dsu.unionSets(base, base + 2);

        EXPECT_EQ(dsu.rank(dsu.find(base)), 2);
    }

    dsu.unionSets(0, 4);
    EXPECT_EQ(dsu.rank(dsu.find(0)), 3);

    dsu.unionSets(0, 8);
    int finalRoot = dsu.find(0);
    for (int i = 0; i < 12; i++) EXPECT_EQ(dsu.find(i), finalRoot);
}