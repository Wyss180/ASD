#ifndef QUEUE
#define QUEUE

#include <stdexcept>

template <class T>
class Queue {
    T* _data;
    int _size;
    int _head;
    int _count;

public:
    Queue(int size = 20) : _size(size), _head(0), _count(0) {
        _data = new T[size];
    }

    ~Queue() {
        delete[] _data;
    }

    void pop() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        _count--;
        _head = (_head+1) % _size;
    }

    void push(const T& value) {
        if (_count >= _size) {
            throw std::logic_error("Queue is full");
        }
        int tail = (_head + _count) % _size;
        _data[tail] = value;
        _count++;
    }

    T& front() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _data[_head];
    }

    bool isEmpty() const {
        return _count == 0;
    }

    void clear() {
        _head = 0;
        _count = 0;
    }
};

#endif