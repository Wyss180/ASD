#include <gtest/gtest.h>
#include "../lib_ITable/UnsortedTableOnTree.h"

TEST(UnsortedTableOnTree, InsertAndFind) {
    UnsortedTableOnTree<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_TRUE(table.consist(5));
    EXPECT_FALSE(table.consist(7));
}

TEST(UnsortedTableOnTree, Erase) {
    UnsortedTableOnTree<int, std::string> table;
    table.insert(5, "five");
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_THROW(table.find(5), std::logic_error);
}

TEST(UnsortedTableOnTree, Print) {
    UnsortedTableOnTree<int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");
    std::stringstream ss;
    table.print(ss);
    EXPECT_TRUE(ss.str().find("(1:one)") != std::string::npos);
    EXPECT_TRUE(ss.str().find("(2:two)") != std::string::npos);
}