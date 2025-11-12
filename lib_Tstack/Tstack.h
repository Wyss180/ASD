#ifndef TSTACK
#define TSTACK

#include "../lib_list/list.h"
#include <stdexcept>

template <class T>
class TStack {
private:
    List<T> _list;
    int _capacity;
public:
    TStack(int capacity = 20) : _capacity(capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Stack capacity must be positive");
        }
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::logic_error("Stack is full");
        }
        _list.push_front(value);
    }

    void pop() {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        _list.pop_front();
    }

    T& top() {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        return _list.front();
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        return _list.front();
    }

    bool isEmpty() const {
        return _list.isEmpty();
    }

    bool isFull() const {
        return _list.size() >= _capacity;
    }

    void clear() {
        _list.clear();
    }

    int size() const {
        return _list.size();
    }

    int capacity() const {
        return _capacity;
    }
};

#endif