#ifndef STACK
#define STACK

#include <stdexcept>

template <class T>
class Stack {
    T* _data;
    int _size;
    int _top;

public:
    Stack(int size = 20) : _size(size), _top(-1) {
        _data = new T[size];
    }

    ~Stack() {
        delete[] _data;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::logic_error("Stack is full");
        }
        _data[++_top] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        _top--;
    }

    T& top() {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        return _data[_top];
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        return _data[_top];
    }

    bool isEmpty() const {
        return _top == -1;
    }

    bool isFull() const {
        return _top == _size - 1;
    }

    void clear() {
        _top = -1;
    }
};

#endif