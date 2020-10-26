#include <fstream>
#include <iostream>

using namespace std;

class TreeNode {
public:
    explicit TreeNode(int key)
            : Key(key) {
    }

    int Key;
    TreeNode *Left = nullptr;
    TreeNode *Right = nullptr;
};

class TTree {
public:
    TTree()
            : Root(nullptr) {
    }

    ~TTree() {
        DestroyNode(Root);
    }

    void Insert(int x) {
        TreeNode **cur = &Root;
        while (*cur) {
            TreeNode &node = **cur;
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

    TreeNode *DeleteKey(TreeNode *root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->Key) {
            root->Left = DeleteKey(root->Left, key);
            return root;
        } else if (key > root->Key) {
            root->Right = DeleteKey(root->Right, key);
            return root;
        }
        if(root->Left == nullptr){
            return root->Right;
        }else if(root->Right == nullptr){
            return root->Left;
        }else {
        int min_key = FindMinKey(root->Right)->Key;
        root->Key = min_key;
        root->Right = DeleteKey(root->Right,min_key);
        return root;
        }
    }
    void PrintPreOrderTraversal(ostream &out) {
        PreOrderTraversal(Root, out);
    }
    void Delete(int key) {
        Root = DeleteKey(Root, key);
    }
private:
    static void DestroyNode(TreeNode *node) {
        if (node) {
            DestroyNode(node->Left);
            DestroyNode(node->Right);
            delete node;
        }
    }

    void PreOrderTraversal(TreeNode *root, ostream &out) {
        if (root == nullptr) {
            return;
        }
        out << root->Key << endl;
        PreOrderTraversal(root->Left, out);
        PreOrderTraversal(root->Right, out);
    }
    TreeNode * FindMinKey(TreeNode* root){
        if(root->Left!=nullptr){
            return FindMinKey(root->Left);
        }
        else return root;
    }
private:
    TreeNode *Root;
};

int main() {
    ifstream in("input.txt");
    int key = 0;
    int value = 0;
    in >> key;
    auto binary_tree = new TTree();
    if (in.is_open()) {
        while (in >> value) {
            binary_tree->Insert(value);
        }
    } else cout << "File is not open";
    in.close();
    binary_tree->Delete(key);
    ofstream out("output.txt");
    binary_tree->PrintPreOrderTraversal(out);
    return 0;
}