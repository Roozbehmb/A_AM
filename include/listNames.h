#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
    
    Node(const string& name) : data(name), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    void insert(const string& name) {
        Node* newNode = new Node(name);
        
        if (head == nullptr || name < head->data) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && name > current->next->data) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
        void display() {
        Node* current = head;
        while (current != nullptr) {
            cout <<"name:\t"<< current->data <<endl;
            current = current->next;
        }
        cout << endl;
    }

private:
    Node* head;
};
int GetLinkedList() {
    LinkedList nameList;

    while (true) {
        cout << "Enter a name (or type '.' to finish): ";
        string name;
        cin >> name;

        if (name == ".") {
            break;
        }

        nameList.insert(name);
    }

    cout << "*****Sorted names**** "<<endl;
    nameList.display();



    return 0;
}
