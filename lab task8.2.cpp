#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int v) {
    if (!root) return new Node(v);
    if (v < root->data) root->left = insert(root->left, v);
    else if (v > root->data) root->right = insert(root->right, v);
    return root;
}
Node* findMin(Node* r) { while (r->left) r = r->left; return r; }

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left && !root->right) {          // leaf
            delete root; return nullptr;
        }
        if (!root->left) {                          // only right child
            Node* t = root->right; delete root; return t;
        }
        if (!root->right) {                         // only left child
            Node* t = root->left; delete root; return t;
        }
        Node* succ = findMin(root->right);          // two children: inorder successor
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}
void inorder(Node* r) { if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); } }

bool isBST(Node* r, long lo, long hi) {
    if (!r) return true;
    if (r->data <= lo || r->data >= hi) return false;
    return isBST(r->left, lo, r->data) && isBST(r->right, r->data, hi);
}

int main() {
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int dels[] = {20, 30, 50};
    Node* root = nullptr;
    for (int v : vals) root = insert(root, v);

    for (int d : dels) {
        root = deleteNode(root, d);
        cout << "After deleting " << d << ": ";
        inorder(root);
        cout << (isBST(root, -2147483648LL, 2147483647LL) ? " [BST valid]" : " [BST INVALID]") << endl;
    }
    return 0;
}
