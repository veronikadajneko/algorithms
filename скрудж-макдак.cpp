#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int _max(std::vector<int> &values) {
    size_t max = 0;
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] + i > max) {
            max = values[i] + i;
        }
    }
    if (values.size() > max) {
        max = values.size();
    }
    return max;
}

void dfs(int v, std::vector<std::vector<int>> &g, int n, std::vector<char> &used, std::vector<int> &width) {
    std::vector<int> values;
    used[v] = 1;
    if (g[v].empty()) {
        width[v] = 0;
    } else {
        for (auto i = g[v].begin(); i != g[v].end(); i++) {
            if (!used[*i]) {
                dfs(*i, g, n, used, width);
                values.push_back(width[*i]);
            }
        }
        sort(values.begin(), values.end(), std::greater<>());
        width[v] = _max(values);
    }
}

bool comp(std::pair<int, int> &lhs, std::pair<int, int> &rhs) {
    if (lhs.first == rhs.first) {
        return lhs.second < rhs.second;
    } else return lhs.first > rhs.first;
}

void priority_dfs(int v, std::vector<std::vector<int>> &g, int n,
                  std::vector<char> &used, std::vector<int> &width, std::vector<int> &num) {
    used[v] = 1;
    std::vector<int> child_width;
    for (int &i : g[v]) {
        child_width.push_back(i);
    }
    sort(child_width.begin(), child_width.end(),
         [&width,&g](int &a, int &b) {
        if(width[a] != width[b]){
            return width[a] > width[b];
        }
        else if(g[a].size() != g[b].size()){
            return g[a].size() > g[b].size();
        }
        else return a < b;

         });
    for (auto &i : child_width) {
        if (!used[i]) {
            priority_dfs(i, g, n, used, width, num);
        }
    }
    num.push_back(v);
}

int main() {
    std::ifstream in("input.txt");
    int n = 1;
    in >> n;
    int function = 1;
    in >> function;
    std::vector<std::vector<int>> graph(n + 1);
    size_t name = 0, quantity = 0, value = 0;
    char tmp;
    for (size_t i = 0; i < n; i++) {
        in >> name >> tmp >> quantity;
        if (quantity != 0) {
            for (size_t j = 0; j < quantity; j++) {
                in >> tmp >> value;
                graph[name].push_back(value);
            }
        }
    }
    std::vector<char> used(n + 1);
    std::vector<int> width(n + 1);
    for (size_t i = 1; i <= n; i++) {
        used[i] = 0;
        width[i] = 0;
    }
    std::ofstream out("output.txt");
    dfs(function, graph, n, used, width);
    out << width[function] << std::endl;
    for (size_t i = 1; i <= n; i++) {
        used[i] = 0;
    }
    std::vector<int> num;
    priority_dfs(function, graph, n, used, width, num);
    int size = num.size();
    for (size_t i = 0; i < size - 1; i++) {
        out << num[i] << " ";
    }
    out << num[size - 1];
    return 0;
}