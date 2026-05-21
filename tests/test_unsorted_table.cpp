#include <gtest/gtest.h>
#include "../lib_ITable/UnsortedTableOnVec.h"

TEST(UnsortedTableOnVec, InsertAndFind) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(3));
}

TEST(UnsortedTableOnVec, Erase) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST(UnsortedTableOnVec, Empty) {
    UnsortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(UnsortedTableOnVec, Print) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    std::stringstream ss;
    table.print(ss);
    EXPECT_EQ(ss.str(), "{ (1, one) (2, two) }");
}

TEST(UnsortedTableOnVec, DuplicateKeysAllowed) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "first");
    table.insert(1, "second");

    EXPECT_EQ(table.find(1), "first");
}