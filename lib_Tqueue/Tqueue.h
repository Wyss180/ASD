#ifndef TQUEUE
#define TQUEUE

#include <stdexcept>
#include "../lib_list/list.h"

template <class T>
class TQueue {
private:
    List<T> _list;

public:
    TQueue() = default;

    void push(const T& value) {
        _list.push_back(value);
    }

    void pop() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        _list.pop_front();
    }

    T& front() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _list.front();
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _list.front();
    }

    T& back() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _list.back();
    }

    const T& back() const {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _list.back();
    }

    bool isEmpty() const {
        return _list.isEmpty();
    }

    void clear() {
        _list.clear();
    }

    int size() const {
        return _list.size();
    }
};

#endif