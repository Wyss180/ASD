#ifndef ALGORITHMS
#define ALGORITHMS
#include <string>
#include <stack>
#include "algorithms.h"
#include "list.h"

bool check_breckets(std::string);

template<class T>
bool cycle(Node<T>* head) {
    if (head == nullptr || head->next == nullptr)
        return false;

    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}


#endif