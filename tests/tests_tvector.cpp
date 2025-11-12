#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVector, no_throw) {
	ASSERT_NO_THROW(TVector<int> vec);
}

TEST(TestTVector, deffault_constructor) {
	TVector<int> vec;

	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 0);
	EXPECT_EQ(vec.data(), nullptr);
}

TEST(TestTVector, create_vector_with_initlist_constructor_and_clear_and_out) {
	TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7 });

	EXPECT_EQ(vec.size(), 7);
	EXPECT_EQ(vec.capacity(), 15);
	EXPECT_NE(vec.data(), nullptr);

	for (int i = 0; i < vec.size(); i++) {
		EXPECT_EQ(vec[i], i + 1);
	}
	EXPECT_EQ(vec[3], 4);
	vec.clear();
	EXPECT_EQ(vec.size(), 7);
	EXPECT_EQ(vec.capacity(), 15);
	EXPECT_EQ(vec.data(), nullptr);
}

TEST(TestTVector, constructors_and_copy_test) {
	int n = 10;
	int* mas = new int[n];
	for (int i = 0; i < n; i++) {
		mas[i] = i;
	}
	TVector<int> vec1(5);
	TVector<int> vec2(mas, 7);
	vec1 = vec2;
	EXPECT_EQ(vec1.size(), 7);
	EXPECT_EQ(vec1.capacity(), 15);
	EXPECT_NE(vec1.data(), nullptr);
	EXPECT_EQ(vec1[3], 3);
	EXPECT_EQ(vec1.find(5), 5);
}

TEST(TestTVector, all_inserts_test) {
	int n = 10;
	int* mas = new int[n];
	for (int i = 0; i < n; i++) {
		mas[i] = i;
	}
	TVector<int> vec(mas, n);
	vec.push_back(11);
	EXPECT_EQ(vec[10], 11);
	vec.push_front(-1);
	EXPECT_EQ(vec[0], -1);
	vec.insert(5, 40);
	EXPECT_EQ(vec[5], 40);
	EXPECT_EQ(vec.front(), -1);
	EXPECT_EQ(vec.back(), 11);
}

TEST(TestTVector, all_pop_test) {
	int n = 10;
	int* mas = new int[n];
	for (int i = 0; i < n; i++) {
		mas[i] = i;
	}
	TVector<int> vec(mas, n);
	vec.pop_back();
	ASSERT_ANY_THROW(vec.find(9));
	EXPECT_EQ(vec.size(), 9);
	vec.erase(3);
	EXPECT_EQ(vec[3], 4);
	EXPECT_EQ(vec.size(), 8);
	ASSERT_ANY_THROW(vec.erase(4, 5););
	vec.pop_front();
	EXPECT_EQ(vec[0], 1);
}

TEST(VectorIteratorTest, empty_vector_iteration) {
	TVector<int> vec;

	EXPECT_TRUE(vec.begin() == vec.end());

	int iteration_count = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		iteration_count++;
	}
	EXPECT_EQ(iteration_count, 0);
}

TEST(VectorIteratorTest, iterator_write_operations) {
	TVector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	int new_value = 10;
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it = new_value;
		new_value += 10;
	}

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 20);
	EXPECT_EQ(vec[2], 30);

	auto it = vec.begin();
	*it = 100;
	EXPECT_EQ(vec[0], 100);

	++it;
	*it = 200;
	EXPECT_EQ(vec[1], 200);
}

TEST(VectorIteratorTest, iterator_read_operations) {
	TVector<int> vec;
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(15);

	auto it = vec.begin();
	EXPECT_EQ(*it, 5);

	++it;
	EXPECT_EQ(*it, 10);

	it++;
	EXPECT_EQ(*it, 15);

	++it;
	EXPECT_TRUE(it == vec.end());
}