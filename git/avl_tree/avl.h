#include <iostream>
#include <vector>
#include <string>
using namespace std;
class avltree;

class Node {
    friend avltree;
    void setheight(); // reset height 
    int balance(); // getting balance factor
    int key, value;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Node(int k, int v, Node* par) : key(k), value(v), parent(par) {}; 
    ~Node() {delete left; delete right;}; 
    void print(); // print at current node
};

class avltree {
    private: // helper functions
        Node* root = nullptr;
        Node* right_rotate(Node*& y);
        Node* left_rotate(Node*& x); 
        Node* restructure(int k, Node*& z);
    public:
        avltree() {};
        ~avltree() {delete root;}
        void search(int k); // serach for key
        void insert(int k, int v); // insert key value pair
        void remove(int k); // remove at key
        void reset(); // reset tree to an empty tree
        void print(); // print at root
};