#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<class T>
class DList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {
        }
    };

    Node* _head;
    Node* _tail;
    size_t _size;

public:
    DList() : _head(nullptr), _tail(nullptr), _size(0) {}

    DList(const DList& other) : _head(nullptr), _tail(nullptr), _size(0) {
        copy_from(other);
    }

    DList(std::initializer_list<T> init) : _head(nullptr), _tail(nullptr), _size(0) {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    ~DList() {
        clear();
    }

    DList& operator=(const DList& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    class Iterator;
    class ConstIterator;

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(_head); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return _head->data;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return _head->data;
    }

    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return _tail->data;
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return _tail->data;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value, nullptr, _head);

        if (_head) {
            _head->prev = new_node;
        }
        else {
            _tail = new_node;
        }
        _head = new_node;
        _size++;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value, _tail, nullptr);

        if (_tail) {
            _tail->next = new_node;
        }
        else {
            _head = new_node;
        }
        _tail = new_node;
        _size++;
    }

    Iterator insert(Iterator pos, const T& value) {
        if (pos == begin()) {
            push_front(value);
            return begin();
        }
        else if (pos == end()) {
            push_back(value);
            return Iterator(_tail);
        }
        else {
            Node* current = pos.current;
            Node* new_node = new Node(value, current->prev, current);

            current->prev->next = new_node;
            current->prev = new_node;
            _size++;

            return Iterator(new_node);
        }
    }

    void pop_front() {
        if (empty()) return;

        Node* temp = _head;
        _head = _head->next;

        if (_head) {
            _head->prev = nullptr;
        }
        else {
            _tail = nullptr;
        }

        delete temp;
        _size--;
    }

    void pop_back() {
        if (empty()) return;

        Node* temp = _tail;
        _tail = _tail->prev;

        if (_tail) {
            _tail->next = nullptr;
        }
        else {
            _head = nullptr;
        }

        delete temp;
        _size--;
    }

    Iterator erase(Iterator pos) {
        if (pos == end()) return end();

        Node* current = pos.current;
        Node* next_node = current->next;

        if (current == _head) {
            pop_front();
        }
        else if (current == _tail) {
            pop_back();
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            _size--;
        }

        return Iterator(next_node);
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    size_t size() const { return _size; }

    bool empty() const { return _size == 0; }

    void reverse() {
        if (_size < 2) return;

        Node* current = _head;
        while (current) {
            std::swap(current->prev, current->next);
            current = current->prev;
        }
        std::swap(_head, _tail);
    }

    void swap(DList& other) {
        std::swap(_head, other._head);
        std::swap(_tail, other._tail);
        std::swap(_size, other._size);
    }

private:
    void copy_from(const DList& other) {
        Node* current = other._head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
};

template<class T>
class DList<T>::Iterator {
private:
    Node* current;

public:
    Iterator(Node* node = nullptr) : current(node) {}

    T& operator*() const {
        if (!current) throw std::runtime_error("Dereferencing null iterator");
        return current->data;
    }

    T* operator->() const { return &current->data; }

    Iterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator& operator--() {
        if (current) current = current->prev;
        return *this;
    }

    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const { return current == other.current; }
    bool operator!=(const Iterator& other) const { return current != other.current; }

    friend class DList<T>;
};

template<class T>
class DList<T>::ConstIterator {
private:
    const Node* current;

public:
    ConstIterator(const Node* node = nullptr) : current(node) {}
    ConstIterator(const Iterator& it) : current(it.current) {}

    const T& operator*() const {
        if (!current) throw std::runtime_error("Dereferencing null iterator");
        return current->data;
    }

    const T* operator->() const { return &current->data; }

    ConstIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    ConstIterator operator++(int) {
        ConstIterator temp = *this;
        ++(*this);
        return temp;
    }

    ConstIterator& operator--() {
        if (current) current = current->prev;
        return *this;
    }

    ConstIterator operator--(int) {
        ConstIterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const ConstIterator& other) const { return current == other.current; }
    bool operator!=(const ConstIterator& other) const { return current != other.current; }
};

#endif