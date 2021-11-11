#include "avl.h"

void Node::print() {
    cout << "key: " << key 
    << " parent: " << (parent ? to_string(parent->key) : "not exsit")
    << " left child: " << (left ? to_string(left->key) : "not exsit") 
    << " right child: " << (right ? to_string(right->key) : "not exsit") << endl;
    if (right) right->print();
    if (left) left->print();
}

void Node::setheight() {
    if (left) { // left exists
        if (right) { // right eixsts get the largest of both + 1 as its height again 
            height = 1 + max(left->height, right->height);
        } else { // onyl left exists
            height = 1 + left->height;
        }
    } else if (right) { // only right exists
        height = 1 + right->height;
    } else { // none exists
        height = 0;
    }
}

int Node::balance() { 
    if (left) { // left exists
        if (right) { // right exists
            return left->height - right->height;
        } else { // only left exists
            return left->height + 1;
        }
    } else if (right) { // only right exists
        return (-1 - right->height);
    } else { // none exists
        return 0;
    }
}

Node* avltree::right_rotate(Node*& y) {
    Node* x = y->left;
    Node* z = x->right;
    x->right = y;
    y->left = z;
    x->parent = y->parent;
    y->parent = x;
    if (z) {
        z->parent = y;
    }    
    y->setheight();
    x->setheight();
    return x;
}

Node* avltree::left_rotate(Node*& x) {
    Node* y = x->right;
    Node* z = y->left;
    y->left = x;
    x->right = z;
    y->parent = x->parent;
    x->parent = y;
    if (z) {
        z->parent = x;
    }    
    x->setheight();
    y->setheight();
    return y;
}

Node* avltree::restructure(int k, Node* &z) {
    int b = z->balance();
    if (b > 1 && k < z->left->key) {
        return right_rotate(z);
    } if (b > 1 && k > z->left->key) {
        z->left = left_rotate(z->left);
        return right_rotate(z);
    } if (b < -1 && k < z->right->key) {
        z->right = right_rotate(z->right);
        return left_rotate(z);
    } if (b < -1 && k > z->right->key) {
        return left_rotate(z);
    }  
    return z;
}

void avltree::reset() {
    delete root;
    root = nullptr;
}

void avltree::print() {
    if (root) {
        root->print();
    } else {
        cout << "EMPTY TREE" << endl;
    }
}

void avltree::search(int k) {
    Node* node = root;
    while (node) {
        if (node->key == k) {
            cout << "Value: " << node->value << endl; //FOUND
            return;
        } else if (k < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    cout << "ERROR: KEY NOT FOUND" << endl; //NOT FOUND
}

void avltree::insert(int k, int v) {
    // Similar to binary serach tree 
    Node* node = root;
    Node* par(nullptr);
    while (node) {
        if (node->key == k) {
            cout << "Warning: KEY ALREADY EXISTS" << endl; 
            return;
        }
        par = node;
        if (k < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (par == nullptr) { 
        root = new Node(k, v, par);
    } else if (k < par->key) {
        par->left = new Node(k, v, par);
        node = par->left;
        par = par->left;
    } else {
        par->right = new Node(k, v, par);
        node = par->right;
        par = par->right;
    }
    while (par) { // reset every height
        par->setheight();
        par = par->parent;
    } 
    while (node) { // node is now the leaf where k is stored
        if (abs(node->balance()) > 1) {
            if (!node->parent) {
                node = restructure(k,node);
                root = node;
            } else {
                bool from_left = false;
                Node* T = node->parent;
                if (node->parent->left) { // check whether the node is from the left or right
                    if (node->parent->left->key == node->key) {
                        from_left = true;
                    }
                } 
                node = restructure(k, node);
                if (from_left) { // update node's parent
                    T->left = node;
                } else {
                    T->right = node;
                }
            }  
            break; // we are done
        }
        node->setheight();
        node = node->parent;
    }
}

void avltree::remove(int k) {
    Node* target = root;
    Node* parent(nullptr);
    while (target && target->key != k) {
        parent = target;
        if (k < target->key) {
            target = target->left;
        } else {
            target = target->right;
        }
    } 
    if (!target) {
        cout << "ERROR: KEY NOT FOUND" << endl;
        return; // k not found
    }
    // find the node to "replacementlace" the target
    Node* replacement(nullptr);
    if (!target->left) {
        replacement = target->right;
    } else if (!target->right) {
        replacement = target->left;
    } else {
        // neither child is NULL:
        // find the replacementlacement node and its parent
        replacement = target->right;
        Node* replacement_par = target;
        while (replacement->left) {
            replacement_par = replacement;
            replacement = replacement->left;
        }
        // update the child links for the replacement and its parent
        replacement->left = target->left;
        if (target->left) target->left->parent = replacement;
        if (replacement_par != target) {
            replacement_par->left = replacement->right;
            if (replacement->right) replacement->right->parent = replacement_par;
            replacement->right = target->right;
            if (target->right) target->right->parent = replacement;
        }
    }
    target->left = nullptr;
    target->right = nullptr;
    delete target;
    if (!parent) {
        root = replacement;
        if (replacement) replacement->parent = nullptr;
    } else if (k > parent->key) {  
        parent->right = replacement;
        if (replacement) replacement->parent = parent;
    } else {
        parent->left = replacement;
        if (replacement) replacement->parent = parent;
    }
    while (replacement) { // reset every hright
        replacement->setheight();
        replacement = replacement->parent;
    }
    // node is the parent of the bst node that was removed
    Node* node = parent;
    while (node) { // node is now the leaf where k is stored
        if (abs(node->balance()) > 1) {
            if (!node->parent) {
                node = restructure(k,node);
                root = node;
            } else {
                bool from_left = false;
                Node* T = node->parent;
                if (node->parent->left) { // check whether the node is from the left or right
                    if (node->parent->left->key == node->key) {
                        from_left = true;
                    }
                } 
                node = restructure(k, node);
                if (from_left) { // update node's parent
                    T->left = node;
                } else {
                    T->right = node; 
                }
            }  
        }
        // always continue up the path and fix if needed
        node->setheight();
        node = node->parent;
    } 
}

