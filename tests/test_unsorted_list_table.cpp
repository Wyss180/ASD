#include <gtest/gtest.h>
#include "../lib_ITable/UnsortedTableOnList.h"

TEST(UnsortedTableOnList, InsertAndFind) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(3));
}

TEST(UnsortedTableOnList, Erase) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST(UnsortedTableOnList, Empty) {
    UnsortedTableOnList<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(UnsortedTableOnList, Print) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    std::stringstream ss;
    table.print(ss);
    EXPECT_EQ(ss.str(), "{ (1, one) (2, two) }");
}

TEST(UnsortedTableOnList, DuplicateKeysAllowed) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "first");
    table.insert(1, "second");
    EXPECT_EQ(table.find(1), "first");
}

TEST(UnsortedTableOnList, Size) {
    UnsortedTableOnList<int, std::string> table;
    EXPECT_EQ(table.size(), 0);
    table.insert(1, "one");
    EXPECT_EQ(table.size(), 1);
    table.insert(2, "two");
    EXPECT_EQ(table.size(), 2);
    table.erase(1);
    EXPECT_EQ(table.size(), 1);
}