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
    else cout << "Duplicate " << v << " ignored\n";
    return root;
}
void preorder(Node* r)  { if (r) { cout << r->data << " "; preorder(r->left); preorder(r->right); } }
void inorder(Node* r)   { if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); } }
void postorder(Node* r) { if (r) { postorder(r->left); postorder(r->right); cout << r->data << " "; } }

int countOneChild(Node* r) {
    if (!r) return 0;
    int c = ((r->left == nullptr) != (r->right == nullptr)) ? 1 : 0;
    return c + countOneChild(r->left) + countOneChild(r->right);
}
int countTwoChildren(Node* r) {
    if (!r) return 0;
    int c = (r->left && r->right) ? 1 : 0;
    return c + countTwoChildren(r->left) + countTwoChildren(r->right);
}
int height(Node* r) {            // height in edges; empty tree = -1
    if (!r) return -1;
    return 1 + max(height(r->left), height(r->right));
}

int main() {
    int scores[] = {45, 25, 65, 15, 35, 55, 75, 30};
    Node* root = nullptr;
    for (int s : scores) root = insert(root, s);

    cout << "Preorder: ";  preorder(root);  cout << endl;
    cout << "Inorder: ";   inorder(root);   cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Nodes with one child: "  << countOneChild(root) << endl;
    cout << "Nodes with two children: " << countTwoChildren(root) << endl;
    cout << "Height (edges): " << height(root) << endl;
    return 0;
}
