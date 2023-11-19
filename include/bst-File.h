#include <iostream>
#include <string>
using namespace std;
struct TreeNode {
    string data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const string& name) : data(name), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const string& name) {
        root = insertRecursive(root, name);
    }

    void display() {
        inOrderTraversal(root);
        cout << endl;
    }

private:
    TreeNode* root;

    TreeNode* insertRecursive(TreeNode* node, const string& name) {
        if (node == nullptr) {
            return new TreeNode(name);
        }

        if (name < node->data) {
            node->left = insertRecursive(node->left, name);
        } else if (name > node->data) {
            node->right = insertRecursive(node->right, name);
        }

        return node;
    }

    void inOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << "name:" << node->data <<endl;
            inOrderTraversal(node->right);
        }
    }
};
