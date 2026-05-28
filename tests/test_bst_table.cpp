#include <gtest/gtest.h>
#include "../lib_ITable/BSTTable.h"

TEST(BSTTableTest, InsertSingleElement) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
}

TEST(BSTTableTest, InsertDuplicateKeyThrows) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    EXPECT_THROW(table.insert(5, "FIVE"), std::logic_error);
}

TEST(BSTTableTest, InsertAscendingOrder) {
    BSTTable<int, std::string> table;
    for (int i = 1; i <= 10; ++i) {
        table.insert(i, "val_" + std::to_string(i));
    }
    EXPECT_FALSE(table.is_empty());
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(table.find(i), "val_" + std::to_string(i));
    }
}

TEST(BSTTableTest, InsertDescendingOrder) {
    BSTTable<int, std::string> table;
    for (int i = 10; i >= 1; --i) {
        table.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(table.find(i), "val_" + std::to_string(i));
    }
}

TEST(BSTTableTest, EraseLeaf) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.erase(3);
    EXPECT_THROW(table.find(3), std::logic_error);
    EXPECT_EQ(table.find(5), "five");
}

TEST(BSTTableTest, EraseNodeWithLeftChild) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(2, "two");
    table.erase(3);
    EXPECT_THROW(table.find(3), std::logic_error);
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(5), "five");
}

TEST(BSTTableTest, EraseNodeWithRightChild) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.erase(3);
    EXPECT_THROW(table.find(3), std::logic_error);
    EXPECT_EQ(table.find(4), "four");
    EXPECT_EQ(table.find(5), "five");
}

TEST(BSTTableTest, EraseNodeWithTwoChildren) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(6, "six");
    table.insert(8, "eight");
    table.erase(7);
    EXPECT_THROW(table.find(7), std::logic_error);
    EXPECT_EQ(table.find(6), "six");
    EXPECT_EQ(table.find(8), "eight");
    EXPECT_EQ(table.find(5), "five");
}

TEST(BSTTableTest, EraseRoot) {
    BSTTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.erase(5);
    EXPECT_THROW(table.find(5), std::logic_error);
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(7), "seven");
}

TEST(BSTTableTest, InsertAndEraseSequence) {
    BSTTable<int, std::string> table;
    for (int i = 0; i < 20; ++i) {
        table.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 0; i < 20; i += 2) {
        table.erase(i);
    }
    for (int i = 0; i < 20; ++i) {
        if (i % 2 == 0)
            EXPECT_THROW(table.find(i), std::logic_error);
        else
            EXPECT_EQ(table.find(i), "val_" + std::to_string(i));
    }
}