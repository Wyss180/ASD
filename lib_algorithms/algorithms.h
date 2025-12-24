#ifndef ALGORITHMS
#define ALGORITHMS
#include <string>
#include "../lib_list/list.h"

bool check_breckets(std::string);

int count_islands(std::vector<std::vector<int>>& field);


template<class T>
bool hasCycle(Node<T>* head) {
    if (!head || !head->next) return false;

    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

template<class T>
bool hasCycleReverse(Node<T>* head) {
    if (!head || !head->next) return false;

    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;
    bool hasCycle = false;

    Node<T>* original_head = head;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;

        if (current == original_head) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        current = prev;
        prev = nullptr;
        Node<T>* temp_next = nullptr;

        while (current != original_head) {
            temp_next = current->next;
            current->next = prev;
            prev = current;
            current = temp_next;
        }
    }
    else {
        current = prev;
        prev = nullptr;
        Node<T>* temp_next = nullptr;

        while (current) {
            temp_next = current->next;
            current->next = prev;
            prev = current;
            current = temp_next;
        }
    }

    return hasCycle;
}

template<class T>
Node<T>* findBreakPointWithMath(Node<T>* head) {
    if (!head) return nullptr;
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) break;
    }

    if (!fast || !fast->next) return nullptr;

    Node<T>* start1 = head;
    while (start1 != fast) {
        start1 = start1->next;
        fast = fast->next;
    }

    int cycleLength = 1;
    Node<T>* temp = start1->next;
    while (temp != start1) {
        cycleLength++;
        temp = temp->next;
    }

    Node<T>* current = head;
    for (int i = 0; i < cycleLength - 1; i++) {
        if (!current) break;
        current = current->next;
    }
    while (current->next != start1) {
        current = current->next;
        start1 = start1->next;
    }

    return current;
}
#endif