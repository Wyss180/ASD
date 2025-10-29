#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(ListTest, create_list) {
    ASSERT_NO_THROW(List<int> list);
}

TEST(ListTest, push_front_and_pop_front) {
    List<int> list;
    list.push_front(10);
    list.push_front(20);

    EXPECT_EQ(list.front(), 20);
    list.pop_front();
    EXPECT_EQ(list.front(), 10);
}

TEST(ListTest, push_back_and_pop_back) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    EXPECT_EQ(list.back(), 20);
    list.pop_back();
    EXPECT_EQ(list.back(), 10);
}

TEST(ListTest, check_empty) {
    List<int> list;
    EXPECT_TRUE(list.isEmpty());

    list.push_front(1);
    EXPECT_FALSE(list.isEmpty());

    list.pop_front();
    EXPECT_TRUE(list.isEmpty());
}

TEST(ListTest, throw_when_empty_front) {
    List<int> list;
    EXPECT_THROW(list.front(), std::runtime_error);
}

TEST(ListTest, throw_when_empty_back) {
    List<int> list;
    EXPECT_THROW(list.back(), std::runtime_error);
}

TEST(ListTest, size_after_operations) {
    List<int> list;
    EXPECT_EQ(list.size(), 0);

    list.push_front(1);
    EXPECT_EQ(list.size(), 1);

    list.push_back(2);
    EXPECT_EQ(list.size(), 2);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);

    list.pop_back();
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, find_existing_element) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* found = list.find(20);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->value, 20);
}

TEST(ListTest, find_non_existing_element) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    Node<int>* found = list.find(30);
    EXPECT_EQ(found, nullptr);
}

TEST(ListTest, insert_at_beginning) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);
    list.insert(0, 1);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, insert_at_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.insert(2, 3);

    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, insert_in_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);

    EXPECT_EQ(list.size(), 3);

    EXPECT_EQ(list.front(), 1);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
}

TEST(ListTest, throw_when_insert_invalid_position) {
    List<int> list;
    EXPECT_THROW(list.insert(-1, 1), std::out_of_range);
    EXPECT_THROW(list.insert(1, 1), std::out_of_range);

    list.push_back(1);
    EXPECT_THROW(list.insert(2, 2), std::out_of_range);
}

TEST(ListTest, erase_from_beginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(0);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, erase_from_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(2);
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, erase_from_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, throw_when_erase_invalid_position) {
    List<int> list;
    EXPECT_THROW(list.erase(-1), std::out_of_range);
    EXPECT_THROW(list.erase(0), std::out_of_range);

    list.push_back(1);
    EXPECT_THROW(list.erase(1), std::out_of_range);
}

TEST(ListTest, clear_list) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_THROW(list.front(), std::runtime_error);
}

TEST(ListTest, copy_constructor) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2(list1);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST(ListTest, assignment_operator) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2 = list1;

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}

//TEST(ListTest, iteration_with_begin_end) {
//    List<int> list;
//    list.push_back(1);
//    list.push_back(2);
//    list.push_back(3);
//
//    std::vector<int> result;
//    for (Node<int>* current = list.begin(); current != list.end(); current = current->next) {
//        result.push_back(current->value);
//    }
//
//    std::vector<int> expected = { 1, 2, 3 };
//    EXPECT_EQ(result, expected);
//}

TEST(ListTest, pop_front_until_empty) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    list.pop_front();
    list.pop_front();

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_NO_THROW(list.pop_front());
}

TEST(ListTest, pop_back_until_empty) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    list.pop_back();
    list.pop_back();

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_NO_THROW(list.pop_back());
}

TEST(ListTest, mixed_operations) {
    List<int> list;

    list.push_front(2);
    list.push_back(3);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);

    list.pop_front();
    list.pop_back();

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 2);

    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(ListTest, string_list) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), "hello");
    EXPECT_EQ(list.back(), "world");

    list.pop_front();
    EXPECT_EQ(list.front(), "world");
}

TEST(ListTest, double_list) {
    List<double> list;
    list.push_back(3.14);
    list.push_back(2.71);

    EXPECT_DOUBLE_EQ(list.front(), 3.14);
    EXPECT_DOUBLE_EQ(list.back(), 2.71);
}

TEST(ListTest, iterator_compare) {
    List<int> list;
    int expected_val = 1;

    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);
    }

    for (List<int>::iterator it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }
}

TEST(ListTest, iterator_insert) {
    List<int> list;

    for (int i = 0; i < 10; i++) {
        list.push_back(0);
    }

    int set_val = 1;
    for (List<int>::iterator it = list.begin(); it != list.end(); it++) {
        *it = set_val;
        set_val++;
    }

    int check_val = 1;
    for (List<int>::iterator it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, check_val);
        check_val++;
    }
}

TEST(ListTest, iterator_create) {
    List<int> list;
    ASSERT_NO_THROW(
        for (List<int>::iterator it = list.begin(); it != list.end(); it++) {
            *it = 0;
        }
    );
}