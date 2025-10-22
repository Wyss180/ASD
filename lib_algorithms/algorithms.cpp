#include <stack>
#include <string>
#include "algorithms.h"

bool check_breckets(std::string str) {
    std::stack<char> stack;

    for (char c : str) {
        if (c == ' ' || c == '\t' || c == '\n') continue;

        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) return false;
            stack.pop();
        }
        else {
            return false;
        }
    }

    return stack.empty();
}