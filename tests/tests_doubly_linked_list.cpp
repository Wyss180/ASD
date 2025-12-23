#include <gtest/gtest.h>
#include "../lib_doubly_linked_list/doubly_linked_list.h"

TEST(DListTest, DefaultConstructor) {
    DList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(DListTest, InitializerList) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
}

TEST(DListTest, CopyConstructor) {
    DList<int> list1 = { 1, 2, 3 };
    DList<int> list2(list1);
    EXPECT_EQ(list2.size(), 3);

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while (it1 != list1.end() && it2 != list2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1; ++it2;
    }
}

TEST(DListTest, AssignmentOperator) {
    DList<int> list1 = { 1, 2, 3 };
    DList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST(DListTest, PushFront) {
    DList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DListTest, PushBack) {
    DList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DListTest, Insert) {
    DList<int> list = { 1, 3, 4 };
    auto it = list.begin();
    ++it;
    list.insert(it, 2);

    std::vector<int> expected = { 1, 2, 3, 4 };
    auto list_it = list.begin();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(*list_it, expected[i]);
        ++list_it;
    }
}

TEST(DListTest, PopFront) {
    DList<int> list = { 1, 2, 3 };
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
}

TEST(DListTest, PopBack) {
    DList<int> list = { 1, 2, 3 };
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(DListTest, Erase) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    auto it = list.begin();
    ++it; ++it;
    it = list.erase(it);

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(*it, 4);

    std::vector<int> expected = { 1, 2, 4, 5 };
    auto list_it = list.begin();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(*list_it, expected[i]);
        ++list_it;
    }
}

TEST(DListTest, Clear) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(DListTest, IteratorForward) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    int expected = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected++);
    }
}

TEST(DListTest, IteratorBackward) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    int expected = 5;
    auto it = list.end();
    while (it != list.begin()) {
        --it;
        EXPECT_EQ(*it, expected--);
    }
}

TEST(DListTest, RangeBasedFor) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    int sum = 0;
    for (const auto& item : list) {
        sum += item;
    }
    EXPECT_EQ(sum, 15);
}

TEST(DListTest, ConstIterator) {
    const DList<int> list = { 1, 2, 3, 4, 5 };
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);
}


TEST(DListTest, Reverse) {
    DList<int> list = { 1, 2, 3, 4, 5 };
    list.reverse();

    std::vector<int> expected = { 5, 4, 3, 2, 1 };
    auto it = list.begin();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(*it, expected[i]);
        ++it;
    }
}

TEST(DListTest, Swap) {
    DList<int> list1 = { 1, 2, 3 };
    DList<int> list2 = { 4, 5, 6, 7 };

    list1.swap(list2);

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list2.front(), 1);
}

TEST(DListTest, EmptyListOperations) {
    DList<int> list;
    EXPECT_NO_THROW(list.pop_front());
    EXPECT_NO_THROW(list.pop_back());
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(DListTest, SingleElement) {
    DList<int> list;
    list.push_front(42);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 42);

    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(DListTest, SelfAssignment) {
    DList<int> list = { 1, 2, 3 };
    list = list;
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DListTest, MoveSemanticsNotImplemented) {
    DList<int> list1 = { 1, 2, 3 };
    DList<int> list2 = std::move(list1);
    EXPECT_NO_THROW(list1.size());
    EXPECT_NO_THROW(list2.size());
}


TEST(DListTest, LargeList) {
    DList<int> list;
    const int N = 1000;

    for (int i = 0; i < N; ++i) {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), N);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), N - 1);

    int expected = 0;
    for (const auto& item : list) {
        EXPECT_EQ(item, expected++);
    }
}

TEST(DListTest, ManyPushPop) {
    DList<int> list;

    for (int i = 0; i < 100; ++i) {
        list.push_front(i);
        list.push_back(i);
    }
    EXPECT_EQ(list.size(), 200);

    for (int i = 0; i < 50; ++i) {
        list.pop_front();
        list.pop_back();
    }
    EXPECT_EQ(list.size(), 100);
}

TEST(DListTest, StringList) {
    DList<std::string> list;
    list.push_back("Hello");
    list.push_back("World");
    list.push_back("!");

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), "Hello");
    EXPECT_EQ(list.back(), "!");

    std::string result;
    for (const auto& str : list) {
        result += str + " ";
    }
    EXPECT_EQ(result, "Hello World ! ");
}

TEST(DListTest, DoubleList) {
    DList<double> list = { 3.14, 2.71, 1.41 };
    double sum = 0;
    for (const auto& num : list) {
        sum += num;
    }
    EXPECT_DOUBLE_EQ(sum, 3.14 + 2.71 + 1.41);
}