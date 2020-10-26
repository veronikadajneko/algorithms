#pragma comment(linker, "/STACK:33554432")
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

void dfs(int v, vector<vector<pair<size_t, size_t>>> &g,
         int n, vector<char> &used, vector<int64_t> &min_vertex, vector<int64_t> &result) {
    int64_t min = INT64_MAX;
    used[v] = 1;
    for (auto i = g[v].begin(); i != g[v].end(); i++) {
        if (!used[(*i).first]) {
            dfs((*i).first, g, n, used, min_vertex, result);
            if ((*i).second + min_vertex[(*i).first] < min) {
                min = (*i).second + min_vertex[(*i).first];
                result[v] = (*i).first;

            }
            min_vertex[v] = min;
        }
    }
}

int main() {
    ifstream in("in.txt");
    size_t n = 1;
    in >> n;
    size_t k = 1, m = 0;
    size_t c = 1, b = 1;
    vector<vector<pair<size_t, size_t >>> graph(n + 1);
    for (size_t i = 0; i < n; i++) {
        in >> k >> m;
        if (m != 0) {
            for (size_t j = 0; j < m; j++) {
                in >> c >> b;
                pair<int, int> value = make_pair(c, b);
                graph[k].push_back(value);
            }
        }
    }
    vector<char> used(n + 1);
    vector<int64_t> result(n + 1);
    vector<int64_t> min_vertex(n + 1);
    for (size_t i = 1; i <= n; i++) {
        used[i] = 0;
    }
    ofstream out("out.txt");
    dfs(1, graph, n, used, min_vertex, result);
    out << min_vertex[1] << endl;
    out << 1;
    for (size_t i = 1; i <= n;) {
        if (result[i] != 0) {
            out << " " << result[i];
            i = result[i];
        } else break;
    }
    return 0;
}