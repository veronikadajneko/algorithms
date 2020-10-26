#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class TreeNode {
public:
    explicit TreeNode(int key)
            : Key(key), Depth(0), Height(0), Children(0) {
    }
    int Key;
    int Depth;
    int Height;
    int Children;
    TreeNode *Left = nullptr;
    TreeNode *Right = nullptr;
};

class TTree {
public:
    TTree()
            : Root(nullptr), count(0), flag(0) {
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
    void PrintTTree(ostream& out){
       Function(Root,out);
       FindAverage(Root,out);
       PreOrderTraversal(Root,out);
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
    void FindDepth(TreeNode* root, int level,ostream& out){
        if (root == nullptr) {
            return;
        }
        root->Depth = level;
        FindDepth(root->Left,level + 1, out);
        FindDepth(root->Right, level + 1, out);
    }
    int FindGreatestWay(int right, int left) {
        if (right > left) {
            return right;
        } else return left;
    }
        void Function(TreeNode *root, ostream &out) {
            if (root == nullptr) {
                return;
            }
            Function(root->Left, out);
            Function(root->Right, out);
            if (root->Left == nullptr && root->Right == nullptr) {
                root->Height = 0;
                root->Children = 1;
            } else if (root->Left == nullptr) {
                root->Height = root->Right->Height + 1;
                root->Children = root->Right->Children + 1;
            } else if (root->Right == nullptr) {
                root->Height = root->Left->Height + 1;
                root->Children = root->Left->Children + 1;
            } else {
                root->Height = FindGreatestWay(root->Right->Height, root->Left->Height) + 1;
                root->Children = root->Right->Children + root->Left->Children + 1;
            }
            if(root->Right!= nullptr && root->Left!= nullptr) {
                if (root->Right->Height == root->Left->Height && root->Right->Children != root->Left->Children) {
                    count++;
                }
            }
        }
        void FindAverage(TreeNode* root, ostream& out){
            if (root == nullptr) {
                return;
            }
            if(count % 2 != 0){
                FindAverage(root ->Left,out);
                if(root->Right!= nullptr && root->Left!= nullptr) {
                    if (root->Right->Height == root->Left->Height && root->Right->Children != root->Left->Children) {
                        flag++;
                        if(flag == (count+1)/2 ){
                            DeleteKey(root, root->Key);
                        }
                    }
                }
                FindAverage(root->Right,out);
            }
            else return;
    }
private:
    TreeNode *Root;
    int count;
    int flag;
};

int main() {
    ifstream in("in.txt");
    int value = 0;
    auto binary_tree = new TTree();
    if (in.is_open()) {
        while (in >> value) {
            binary_tree->Insert(value);
        }
    } else cout << "File is not opened";
    in.close();
    ofstream out("out.txt");
    binary_tree->PrintTTree(out);
    return 0;
}