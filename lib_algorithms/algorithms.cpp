#include <stack>
#include <vector>
#include "algorithms.h"
#include <string>
#include "../lib_DSU/DSU.h"
#include "../lib_TVector/Tvector.h"
#include "../lib_list/list.h"

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

int count_islands(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int rows = matrix.size(), cols = matrix[0].size();
    DSU dsu(rows * cols);
    int islands = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                islands++;
                int pos = i * cols + j;

                if (j > 0 && matrix[i][j - 1] == 1) {
                    if (dsu.find(pos) != dsu.find(pos - 1)) {
                        dsu.unionSets(pos, pos - 1);
                        islands--;
                    }
                }
                if (i > 0 && matrix[i - 1][j] == 1) {
                    if (dsu.find(pos) != dsu.find(pos - cols)) {
                        dsu.unionSets(pos, pos - cols);
                        islands--;
                    }
                }
            }
        }
    }

    return islands;
}