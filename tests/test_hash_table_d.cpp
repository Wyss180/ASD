#include <gtest/gtest.h>
#include "HashTableD.h"

TEST(HashTableDTest, InsertAndFind) {
    HashTableD<int> table(10);
    table.insert("one", 1);
    table.insert("two", 2);
    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_TRUE(table.consist("one"));
    EXPECT_FALSE(table.consist("three"));
}

TEST(HashTableDTest, Overwrite) {
    HashTableD<int> table(10);
    table.insert("cat", 10);
    table.insert("act", 20);
    EXPECT_EQ(table.find("act"), 20);
}

TEST(HashTableDTest, Erase) {
    HashTableD<int> table(10);
    table.insert("a", 100);
    table.erase("a");
    EXPECT_THROW(table.find("a"), std::runtime_error);
    EXPECT_FALSE(table.consist("a"));
}

TEST(HashTableDTest, IsEmpty) {
    HashTableD<int> table(10);
    EXPECT_TRUE(table.is_empty());
    table.insert("k", 42);
    EXPECT_FALSE(table.is_empty());
    table.erase("k");
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableDTest, ManyElements) {
    HashTableD<int> table(50);
    for (int i = 0; i < 40; ++i) {
        table.insert("key" + std::to_string(i), i);
    }
    for (int i = 0; i < 40; ++i) {
        EXPECT_EQ(table.find("key" + std::to_string(i)), i);
    }
}

TEST(HashTableDTest, Print) {
    HashTableD<int> table(5);
    table.insert("one", 1);
    table.insert("two", 2);
    std::ostringstream oss;
    table.print(oss);
    std::string out = oss.str();
    EXPECT_FALSE(out.empty());
    EXPECT_TRUE(out.find("one") != std::string::npos);
}