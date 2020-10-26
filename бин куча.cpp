#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    int n = 0;
    in >> n;
    int array[100000];
    int key;
    for (int j = 1; j <= n; j++) {
        in >> array[j];
    }

    int i;
    int flag = 0;
    for (i = 1; i <= n; i++) {
        if ((2 * i <= n) && (array[i] > array[2 * i])) {
         flag = 1;break; }

        if ((2 * i + 1 <= n) && (array[i] > array[2 * i + 1])) {
        flag = 1;break; }
    }
    ofstream out("output.txt");
    if (flag!=0) {
        out << "No";
    } else out << "Yes";
    return 0;
}