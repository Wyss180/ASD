#include <stack>
#include "algorithms.h"
#include "list.h"
#include <string>

using std::string;

bool check_breckets(std::string str) {
    std::stack<char> stack;

    if (str.empty()) {
        return true;
    }

    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) {
                return false;
            }

            if ((c == ')' && stack.top() != '(') ||
                (c == ']' && stack.top() != '[') ||
                (c == '}' && stack.top() != '{')) {
                return false;
            }
            stack.pop();
        }
        else {
            return false;
        }
    }

    return stack.empty();
}