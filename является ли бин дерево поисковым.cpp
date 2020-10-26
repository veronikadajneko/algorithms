#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct TreeNode {
    int Key{};
    int max{};
    int min{};
    int parent{};
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

int main() {
    ifstream in("bst.in");
    int count = 0;
    in >> count;
    vector<TreeNode> binary_tree(count);
    in >> binary_tree[0].Key;
    binary_tree[0].max = binary_tree[0].Key;
    binary_tree[0].parent = -1;
    for (size_t i = 1; i < count; i++) {
        char direction;
        in >> binary_tree[i].Key >> binary_tree[i].parent >> direction;
        --binary_tree[i].parent;
        binary_tree[i].max = binary_tree[i].min = binary_tree[i].Key;
        if (direction == 'L') {
            binary_tree[binary_tree[i].parent].left = &binary_tree[i];

        } else {
            binary_tree[binary_tree[i].parent].right = &binary_tree[i];
        }
    }
    bool flag = true;
    for (int i = count - 1; i >= 0; i--) {
        if (binary_tree[i].right != nullptr) {
            if (binary_tree[i].Key <= binary_tree[i].right->min) {
                binary_tree[i].max = binary_tree[i].right->max;
            } else {
                flag = false;
                break;
            }
        }
        if (binary_tree[i].left != nullptr) {
            if (binary_tree[i].Key > binary_tree[i].left->max) {
                binary_tree[i].min = binary_tree[i].left->min;
            }
            else {
                flag = false;
                break;
            }
        }
    }

    ofstream out("bst.out");
    if (flag) {
        out << "YES";
    } else out << "NO";
    return 0;
}