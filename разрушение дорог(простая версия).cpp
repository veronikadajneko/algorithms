#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int find(int x, vector<int> &vertices) {
    while (x != vertices[x]) {
        x = vertices[x];
    }
    return x;
}

void union_set(int rx, int ry, vector<int> &rate, vector<int> &vertices) {
    if (rx == ry)
        return;
    if (rate[rx] < rate[ry]) {
        vertices[rx] = ry;
        rate[ry] += rate[rx];
    } else {
        vertices[ry] = rx;
        rate[rx] += rate[ry];
    }
}

int comp(int x, int y, int &component, vector<int> &rate, vector<int> &vertices) {
    int prx = find(x, vertices);
    int pry = find(y, vertices);
    if (prx != pry) {
        component -= 1;
        union_set(prx, pry, rate, vertices);
    }
    return component;
}

int main() {
    ifstream in("input.txt");
    int n = 1, q = 1, m = 1;
    in >> n >> m >> q;
    vector<int> vertices(n + 1);
    vector<int> rate(n + 1);
    ofstream out("output.txt");
    int u = 1, v = 1;
    for (size_t i = 1; i <= n; i++) {
        vertices[i] = i;
        rate[i] = 1;
    }
    vector<pair<int, int>> edges(m + 1);
    for (size_t i = 1; i <= m; i++) {
        in >> u >> v;
        edges[i] = {u, v};

    }
    vector<int> number(q + 1);
    vector<int> flag(m + 1);
    for (size_t i = 1; i <= q; i++) {
        in >> number[i];
        int value = number[i];
        flag[value] = 1;
    }
    int component = n;
    for (size_t i = 1; i <= m; i++) {
        if (flag[i] == 0) {
            comp(edges[i].first, edges[i].second, component, rate, vertices);
        }
    }
    string result;
    for (size_t i = q; i >= 1; i--) {
        if (component == 1) {
            result += '1';
        } else result += '0';
        int value = number[i];
        int x = edges.at(value).first, y = edges.at(value).second;
        comp(x, y, component, rate, vertices);
    }
    reverse(result.begin(), result.end());
    out << result;
    return 0;
}