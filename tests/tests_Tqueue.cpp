#include <gtest/gtest.h>
#include "../lib_Tqueue/Tqueue.h"
#include "../lib_list/list.h"

TEST(TQueueTest, Empty) {
    TQueue<int> q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0);
}

TEST(TQueueTest, PushPop) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
}

TEST(TQueueTest, NoOverflow) {
    TQueue<int> q;
    for (int i = 0; i < 100; i++) {
        q.push(i);
    }
    EXPECT_EQ(q.size(), 100);
}

TEST(TQueueTest, Underflow) {
    TQueue<int> q;
    EXPECT_THROW(q.pop(), std::logic_error);
    EXPECT_THROW(q.front(), std::logic_error);
    EXPECT_THROW(q.back(), std::logic_error);
}

TEST(TQueueTest, Back) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.back(), 2);
}

TEST(TQueueTest, Clear) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.clear();
    EXPECT_TRUE(q.isEmpty());
}

TEST(TQueueTest, FIFO_Order) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_TRUE(q.isEmpty());
}
