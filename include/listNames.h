#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
    
    Node(const string& name) : data(name), next(nullptr) {}
};
