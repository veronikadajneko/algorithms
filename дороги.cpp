#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int find(int x, vector<int> &cities) {
    while (x != cities[x]) {
        x = cities[x];
    }
    return x;
}

void union_set(int rx, int ry, vector<int> &size, vector<int> &cities) {
    if (rx == ry)
        return;
    if (size[rx] < size[ry]) {
        cities[rx] = ry;
        size[ry] += size[rx];
    } else {
        cities[ry] = rx;
        size[rx] += size[ry];
    }
}

int comp(int x, int y, int& component, vector<int> &size, vector<int> &cities) {
    int prx = find(x,cities);
    int pry = find(y,cities);
    if (prx!=pry) {
        component -= 1;
        union_set(prx, pry, size, cities);
    }
    return component;
}

int main() {
    ifstream in("input.txt");
    int n = 1, q = 1;
    in >> n >> q;
    vector<int> cities(n + 1);
    vector<int> size(n + 1);
    ofstream out("output.txt");
    int u = 1, v = 1;
    for (size_t i = 1; i <= n; i++) {
        cities[i] = i;
        size[i] = 1;
    }
    int component = n;
    for (size_t i = 0; i < q; i++) {
        in >> u >> v;
        out << comp(u,v,component,size,cities);
        out << "\n";
    }
    return 0;
}