#include <stack>
#include <vector>
#include "algorithms.h"
#include <string>
#include "../lib_DSU/DSU.h"
#include "../lib_TVector/Tvector.h"

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

int count_islands(std::vector<std::vector<int>>& field) {
    if (field.empty() || field[0].empty()) {
        return 0;
    }

    int rows = field.size();
    int cols = field[0].size();

    DSU dsu(rows * cols);

    int islandCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == 1) {
                islandCount++;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == 1) {
                int current_id = i * cols + j;

                if (j + 1 < cols && field[i][j + 1] == 1) {
                    int right_id = i * cols + (j + 1);
                    if (dsu.find(current_id) != dsu.find(right_id)) {
                        dsu.unionSets(current_id, right_id);
                        islandCount--;
                    }
                }
                if (i + 1 < rows && field[i + 1][j] == 1) {
                    int down_id = (i + 1) * cols + j;
                    if (dsu.find(current_id) != dsu.find(down_id)) {
                        dsu.unionSets(current_id, down_id);
                        islandCount--;
                    }
                }
            }
        }
    }

    return islandCount;
}