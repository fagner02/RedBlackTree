#include <iostream>
#include <map>
#include <cmath>
using namespace std;

//Compiler version g++ 6.3.0
class node {
public:
    node(int value) :value(value) {

    }
    int value = -1;
    node* parent = nullptr;
    node* left = nullptr;
    node* right = nullptr;
    string color = "r";
    bool root = false;
    int height = 0;
};

string printTree(map<int, node*> nodes, int level, int height) {
    map<int, node*> temp;

    string res = "";
    bool done = true;
    for (int i = 1; i <= pow(2, level - 1);i++) {
        if (i == 1 && height >= level) {
            cout << "\n" << string(
                pow(2, height - level) - 1, ' ');
        }
        if (nodes[i] == nullptr) {
            cout << " " << string(
                pow(2, height - level + 1) - 1, ' ');

            continue;
        }
        done = false;
        cout << nodes[i]->value << nodes[i]->color << string(
            pow(2, height - level + 1) - 1, ' ');
        temp[i * 2 - 1] = nodes[i]->left;
        temp[i * 2] = nodes[i]->right;
    }
    if (done) {
        return res;
    }
    printTree(temp, level + 1, height);
    return res;
}

node* insert(int value, node* root) {
    if (root == nullptr) {
        node* n = new node(value);
        n->root = true;
        n->color = "b";
        return n;
    }
    root->height++;
    if (value > root->value) {
        if (root->right != nullptr) {
            return insert(value, root->right);
        } else {
            node* n = new node(value);
            root->right = n;
            n->parent = root;
            return n;
        }
    } else {
        if (root->left != nullptr) {
            return insert(value, root->left);
        } else {
            node* n = new node(value);
            root->left = n;
            n->parent = root;
            return n;
        }
    }
}
node* restructureTree(node* x);

node* turnBlack(node* z) {
    z->left->color = "b";
    z->right->color = "b";
    if (!z->root) {
        z->color = "r";
        return restructureTree(z);
    }
    return z;
}

void setParent(node* z, node* parent, node* child) {
    if (parent == nullptr) {
        child->root = true;
        return;
    }
    if (z->value > parent->value) {
        parent->right = child;
    } else {
        parent->left = child;
    }
}

node* restructureTree(node* x) {
    node* root = x;

    if (x->parent == nullptr) {
        return root;
    }

    node* y = x->parent;
    node* z = y->parent;

    if (y->color != "r") {
        return root;
    }

    string zLeftColor = (z->left == nullptr) ?
        "b" : z->left->color;
    string zRightColor = (z->right == nullptr) ?
        "b" : z->right->color;

    if (y->value > z->value) {
        if (zLeftColor == "b") {
            if (x->value > y->value) {
                z->color = "r";
                x->color = "r";
                y->color = "b";
                z->right = y->left;
                y->left = z;
                setParent(z, z->parent, y);
                root = y;
            } else {
                x->color = "b";
                z->color = "r";
                y->color = "r";
                z->right = x->left;
                y->left = x->right;
                x->left = z;
                x->right = y;
                setParent(z, z->parent, x);
                root = x;
            }
        } else {
            root = turnBlack(z);
        }
    } else {
        if (zRightColor == "b") {
            if (x->value < y->value) {
                z->color = "r";
                x->color = "r";
                y->color = "b";
                z->left = y->right;
                y->right = z;
                setParent(z, z->parent, y);
                root = y;
            } else {
                x->color = "b";
                z->color = "r";
                y->color = "r";
                z->left = x->right;
                y->right = x->left;
                x->left = y;
                x->right = z;
                setParent(z, z->parent, x);
                root = x;
            }
        } else {
            root = turnBlack(z);
        }
    }
    return root;
}

void add(int value, node*& root) {
    node* addedNode = insert(value, root);
    node* newRoot = restructureTree(addedNode);
    if (newRoot->root) {
        root = newRoot;
    }
}

int main() {
    node* root = nullptr;
    add(10, root);
    add(7, root);
    add(42, root);
    add(31, root);
    add(64, root);
    add(29, root);
    add(83, root);
    add(50, root);
    add(5, root);
    add(23, root);
    add(89, root);
    cout << printTree({ {1,root} }, 1, 5);
}