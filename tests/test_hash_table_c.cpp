#include <gtest/gtest.h>
#include <sstream>
#include "HashTableC.h"

TEST(HashTableCTest, InsertAndFind) {
    HashTableC<int> table(5);
    table.insert("one", 1);
    table.insert("two", 2);
    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_TRUE(table.consist("one"));
    EXPECT_FALSE(table.consist("three"));
}

TEST(HashTableCTest, OverwriteKey) {
    HashTableC<int> table;
    table.insert("cat", 10);
    table.insert("act", 20);
    EXPECT_EQ(table.find("act"), 20);
}

TEST(HashTableCTest, Erase) {
    HashTableC<int> table;
    table.insert("a", 100);
    table.erase("a");
    EXPECT_THROW(table.find("a"), std::runtime_error);
    EXPECT_FALSE(table.consist("a"));
    EXPECT_NO_THROW(table.erase("b"));
}

TEST(HashTableCTest, IsEmpty) {
    HashTableC<int> table(3);
    EXPECT_TRUE(table.is_empty());
    table.insert("key", 42);
    EXPECT_FALSE(table.is_empty());
    table.erase("key");
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableCTest, Merge) {
    HashTableC<int> t1;
    t1.insert("a", 1);
    t1.insert("b", 2);
    HashTableC<int> t2;
    t2.insert("b", 20);
    t2.insert("c", 30);
    t1.merge(t2);
    EXPECT_EQ(t1.find("a"), 1);
    EXPECT_EQ(t1.find("b"), 20);
    EXPECT_EQ(t1.find("c"), 30);
    EXPECT_TRUE(t1.consist("a"));
    EXPECT_TRUE(t1.consist("b"));
    EXPECT_TRUE(t1.consist("c"));
}

TEST(HashTableCTest, Print) {
    HashTableC<int> table(3);
    table.insert("one", 1);
    table.insert("two", 2);
    std::ostringstream oss;
    table.print(oss);
    std::string out = oss.str();
    EXPECT_FALSE(out.empty());
    EXPECT_TRUE(out.find("one") != std::string::npos);
    EXPECT_TRUE(out.find("two") != std::string::npos);
}

TEST(HashTableCTest, ManyElements) {
    HashTableC<int> table(100);
    for (int i = 0; i < 200; ++i) {
        table.insert("key" + std::to_string(i), i);
    }
    for (int i = 0; i < 200; ++i) {
        EXPECT_EQ(table.find("key" + std::to_string(i)), i);
    }
}

TEST(HashTableCTest, StringValue) {
    HashTableC<std::string> table;
    table.insert("pi", "3.14");
    table.insert("e", "2.71");
    EXPECT_EQ(table.find("pi"), "3.14");
    EXPECT_EQ(table.find("e"), "2.71");
}