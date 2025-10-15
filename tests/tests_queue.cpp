#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(QueueTest, create_queue) {
    ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(QueueTest, push_and_pop) {
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    EXPECT_EQ(q.front(), 10);
    q.pop();
    EXPECT_EQ(q.front(), 20);
}

TEST(QueueTest, check_empty) {
    Queue<int> q(3);
    EXPECT_TRUE(q.isEmpty());

    q.push(1);
    EXPECT_FALSE(q.isEmpty());

    q.pop();
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, throw_when_empty) {
    Queue<int> q(3);
    EXPECT_THROW(q.pop(), std::logic_error);
    EXPECT_THROW(q.front(), std::logic_error);
}

TEST(QueueTest, throw_when_full) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);

    EXPECT_THROW(q.push(3), std::logic_error);
}

TEST(QueueTest, circular_behavior) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop(); // _head = 1
    q.pop(); // _head = 2

    q.push(4); // tail = (2 + 1) % 3 = 0
    q.push(5); // tail = (2 + 2) % 3 = 1

    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_EQ(q.front(), 4);
}
