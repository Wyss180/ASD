#include <gtest/gtest.h>
#include "../lib_ITable/SortedTableOnVec.h"

TEST(SortedTableOnVec, InsertAndFind) {
    SortedTableOnVec<int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(SortedTableOnVec, InsertMaintainsOrder) {
    SortedTableOnVec<int, std::string> table;
    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");

    std::stringstream ss;
    table.print(ss);
    EXPECT_EQ(ss.str(), "{ (1, one) (3, three) (5, five) }");
}

TEST(SortedTableOnVec, OverwriteOnDuplicate) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "first");
    table.insert(1, "second");

    EXPECT_EQ(table.find(1), "second");
}

TEST(SortedTableOnVec, Erase) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.erase(1);

    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST(SortedTableOnVec, EraseNonExistentThrows) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.erase(99), std::logic_error);
}

TEST(SortedTableOnVec, Empty) {
    SortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(SortedTableOnVec, BinarySearchPerformance) {
    SortedTableOnVec<int, std::string> table;
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "val" + std::to_string(i));
    }

    EXPECT_TRUE(table.consist(50));
    EXPECT_FALSE(table.consist(150));
}