#include <gtest/gtest.h>
#include "../lib_ITable/BSTTable.h"

TEST(BSTTable, InsertAndFind) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");

    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(8), "eight");
    EXPECT_EQ(table.find(1), "one");
    EXPECT_THROW(table.find(99), std::logic_error);
    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(99));
}

TEST(BSTTable, Erase) {
    BSTTable<int, std::string> table;
    table.insert(10, "ten");
    table.insert(5, "five");
    table.insert(15, "fifteen");
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_THROW(table.find(5), std::logic_error);
    EXPECT_EQ(table.find(10), "ten");
    EXPECT_EQ(table.find(15), "fifteen");
    table.erase(10);
    EXPECT_FALSE(table.consist(10));
    EXPECT_EQ(table.find(15), "fifteen");
}

TEST(BSTTable, PrintSortedOrder) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");

    std::stringstream ss;
    table.print(ss);
    std::string output = ss.str();
    EXPECT_TRUE(output.find("1:one") != std::string::npos);
    EXPECT_TRUE(output.find("2:two") != std::string::npos);
    EXPECT_TRUE(output.find("5:five") != std::string::npos);
    EXPECT_TRUE(output.find("8:eight") != std::string::npos);
    size_t pos1 = output.find("1:one");
    size_t pos2 = output.find("2:two");
    size_t pos5 = output.find("5:five");
    size_t pos8 = output.find("8:eight");
    EXPECT_LT(pos1, pos2);
    EXPECT_LT(pos2, pos5);
    EXPECT_LT(pos5, pos8);
}

TEST(BSTTable, Empty) {
    BSTTable<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_THROW(table.find(1), std::logic_error);
    EXPECT_FALSE(table.consist(1));
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(BSTTable, DuplicateInsertThrows) {
    BSTTable<int, std::string> table;
    table.insert(1, "first");
    EXPECT_THROW(table.insert(1, "second"), std::logic_error);
    EXPECT_EQ(table.find(1), "first");
}