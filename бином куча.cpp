#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("input.txt");
    int64_t n;
    in >> n;
    vector<int> binary_repres;
    while (n != 0) {
        if (n % 2 == 0) {
            binary_repres.push_back(0);
        } else binary_repres.push_back(1);
        n /= 2;
    }
    ofstream out("output.txt");
    for(size_t i = 0; i < binary_repres.size();i++){
        if(binary_repres.at(i) == 1){
            out << i << endl;
        }
    }
    return 0;
}