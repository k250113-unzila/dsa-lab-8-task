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

int printRange(Node* r, int L, int R) {
    if (!r) return 0;
    int cnt = 0;
    if (r->data > L) cnt += printRange(r->left, L, R);
    if (r->data >= L && r->data <= R) { cout << r->data << " "; cnt++; }
    if (r->data < R) cnt += printRange(r->right, L, R);
    return cnt;
}

void freeTree(Node* n) {
    if (!n) return;
    freeTree(n->left);
    freeTree(n->right);
    delete n;
}


Node* deleteOutside(Node* r, int L, int R) {
    if (!r) return nullptr;
    if (r->data < L) {                
        Node* rightPart = deleteOutside(r->right, L, R);
        r->right = nullptr;
        freeTree(r->left);
        delete r;
        return rightPart;
    }
    if (r->data > R) {                 
        Node* leftPart = deleteOutside(r->left, L, R);
        r->left = nullptr;
        freeTree(r->right);
        delete r;
        return leftPart;
    }
    r->left = deleteOutside(r->left, L, R);
    r->right = deleteOutside(r->right, L, R);
    return r;
}
void inorder(Node* r) { if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); } }

int main() {
    int ids[] = {50, 25, 75, 10, 30, 60, 90, 20, 40, 70, 80};
    int L = 25, R = 70;
    Node* root = nullptr;
    for (int id : ids) root = insert(root, id);

    cout << "IDs in range: ";
    int count = printRange(root, L, R);
    cout << endl << "Count: " << count << endl;

    root = deleteOutside(root, L, R);
    cout << "After deleting outside range: ";
    inorder(root);
    cout << endl;
    return 0;
}
