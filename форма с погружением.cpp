#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Element {
    int i;
    int j;
    int priority;
};

bool operator<(const Element &lhs, const Element &rhs) {
    return lhs.priority > rhs.priority;
}

int Max(int &a, int &b) {
    if (a > b) {
        return a;
    } else return b;
}

void findResult(int n, int m, vector<vector<int>> &a, vector<vector<int>> &b, ostream &out) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            sum += a[i][j] - b[i][j];

        }
    }
    out << sum;
}

int main() {
    ifstream in("in.txt");
    int n = 1, m = 1;
    in >> n >> m;
    vector<vector<int>> form(n, vector<int>(m));
    vector<vector<int>> B(n, vector<int>(m));
    priority_queue<Element> border;
    bool used[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> form[i][j];
            used[i][j] = false;
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                border.push({i, j, form[i][j]});
                B[i][j] = form[i][j];
            } else {
                B[i][j] =   INT32_MAX;
            }
        }
    }

    while (!border.empty()) {
        Element current = border.top();
        border.pop();
        if (used[current.i][current.j]) {
            continue;
        } else {
            B[current.i][current.j] = current.priority;
            used[current.i][current.j] = true;
            if (current.i - 1 >= 0 && current.i - 1 <= n - 1 && !used[current.i - 1][current.j]) {
                if (B[current.i - 1][current.j] > B[current.i][current.j]) {
                    border.push({current.i - 1, current.j,
                                 Max(B[current.i][current.j], form[current.i - 1][current.j])});
                }
            }
            if (current.j - 1 >= 0 && current.j - 1 <= m - 1 && !used[current.i][current.j - 1]) {
                if (B[current.i][current.j - 1] > B[current.i][current.j]) {
                    border.push({current.i, current.j - 1,
                                 Max(B[current.i][current.j], form[current.i][current.j - 1])});
                }
            }
            if (current.i + 1 <= n - 1 && !used[current.i + 1][current.j]) {
                if (B[current.i + 1][current.j] > B[current.i][current.j]) {
                    border.push({current.i + 1, current.j,
                                 Max(B[current.i][current.j], form[current.i + 1][current.j])});
                }
            }
            if (current.j + 1 <= m - 1 && !used[current.i][current.j + 1]) {
                if (B[current.i][current.j + 1] > B[current.i][current.j]) {
                    border.push({current.i, current.j + 1,
                                 Max(B[current.i][current.j], form[current.i][current.j + 1])});
                }
            }
        }
    }
    ofstream out("out.txt");
    findResult(n, m, B, form, out);

    return 0;
}