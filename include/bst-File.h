#include <iostream>
#include <string>
using namespace std;
struct TreeNode {
    string data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const string& name) : data(name), left(nullptr), right(nullptr) {}
};