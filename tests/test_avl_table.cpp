#include <gtest/gtest.h>
#include "../lib_ITable/AVLTable.h"

TEST(AVLTableBalanceTest, Insert10Root100To50) {
    AVLTable<int, std::string> table;

    table.insert(100, "hundred");
    table.insert(50, "fifty");
    table.insert(150, "one fifty");
    table.insert(25, "twenty five");
    table.insert(75, "seventy five");
    table.insert(175, "one seventy five");
    table.insert(20, "twenty");
    table.insert(30, "thirty");
    table.insert(60, "sixty");
    table.insert(80, "eighty");

    ASSERT_EQ(table.root(), 100);

    table.insert(10, "ten");

    EXPECT_EQ(table.root(), 50);

    for (int k : {10, 20, 25, 30, 50, 60, 75, 80, 100, 150, 175}) {
        EXPECT_NO_THROW(table.find(k));
    }
}

TEST(AVLTableDeleteTest, Erase25Root40To60) {
    AVLTable<int, std::string> table;

    table.insert(40, "forty");
    table.insert(20, "twenty");
    table.insert(60, "sixty");
    table.insert(15, "fifteen");
    table.insert(25, "twenty five");
    table.insert(50, "fifty");
    table.insert(70, "seventy");
    table.insert(5, "five");
    table.insert(45, "forty five");
    table.insert(55, "fifty five");
    table.insert(65, "sixty five");
    table.insert(80, "eighty");
    table.insert(75, "seventy five");

    ASSERT_EQ(table.root(), 40);

    table.erase(25);

    EXPECT_EQ(table.root(), 60);

    EXPECT_THROW(table.find(25), std::logic_error);

    std::vector<int> remaining = { 5,15,20,40,45,50,55,60,65,70,75,80 };
    for (int k : remaining) {
        EXPECT_NO_THROW(table.find(k));
    }
}