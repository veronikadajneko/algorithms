#include <fstream>
#include <iostream>

using namespace std;

class TreeNode{
public:
    TreeNode(int key)
            : Key(key)
    {
    }

    int Key;
    TreeNode* Left = nullptr;
    TreeNode* Right = nullptr;
};

class TTree {
public:
    TTree()
            : Root(nullptr)
    {
    }

    ~TTree() {
        DestroyNode(Root);
    }
    void Insert(int x) {
        TreeNode** cur = &Root;
        while (*cur) {
            TreeNode& node = **cur;
            if (x < node.Key) {
                cur = &node.Left;
            } else if (x > node.Key) {
                cur = &node.Right;
            } else {
                return;
            }
        }
        *cur = new TreeNode(x);
    }
   void PrintPreOrderTraversal(ostream& out){
         PreOrderTraversal(Root,out);
    }
private:
    static void DestroyNode(TreeNode* node) {
        if (node) {
            DestroyNode(node->Left);
            DestroyNode(node->Right);
            delete node;
        }
    }
    static void PreOrderTraversal(TreeNode* root, ostream& out){
        if(root == nullptr){
            return;
        }
        out << root->Key << endl;
        PreOrderTraversal(root->Left,out);
        PreOrderTraversal(root->Right,out);
    }
private:
    TreeNode* Root;
};

int main(){
    ifstream in("input.txt");
    int value = 0;
    auto binary_tree = new TTree();
    if(in.is_open()) {
        while (!in.eof()) {
            in >> value;
            binary_tree->Insert(value);
        }
    }
    else cout << "File is not open";
    in.close();
    ofstream out("output.txt");
    binary_tree->PrintPreOrderTraversal(out);

    return 0;
}