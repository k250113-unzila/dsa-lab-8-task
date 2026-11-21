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
void inorder(Node* r) { if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); } }

int findMin(Node* r) { while (r->left) r = r->left; return r->data; }
int findMax(Node* r) { while (r->right) r = r->right; return r->data; }

void printGreater(Node* r, double threshold) {
    if (!r) return;
    if (r->data > threshold) printGreater(r->left, threshold);
    if (r->data > threshold) cout << r->data << " ";
    printGreater(r->right, threshold);
}

int countTwoChildren(Node* r) {
    if (!r) return 0;
    return ((r->left && r->right) ? 1 : 0) + countTwoChildren(r->left) + countTwoChildren(r->right);
}

int height(Node* r) { return r ? 1 + max(height(r->left), height(r->right)) : -1; }

void printLongestPath(Node* r) {
    if (!r) return;
    cout << r->data;
    if (!r->left && !r->right) return;
    cout << " -> ";
    if (height(r->left) >= height(r->right)) printLongestPath(r->left);
    else printLongestPath(r->right);
}

bool isSkewed(Node* r) {
    if (!r) return true;
    if (r->left && r->right) return false;
    return isSkewed(r->left) && isSkewed(r->right);
}

Node* findMinNode(Node* r) { while (r->left) r = r->left; return r; }

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left && !root->right) { delete root; return nullptr; }
        if (!root->left) { Node* t = root->right; delete root; return t; }
        if (!root->right) { Node* t = root->left; delete root; return t; }
        Node* s = findMinNode(root->right);
        root->data = s->data;
        root->right = deleteNode(root->right, s->data);
    }
    return root;
}

Node* findOneChildNode(Node* r) {
    if (!r) return nullptr;
    if ((r->left == nullptr) != (r->right == nullptr)) return r;
    Node* x = findOneChildNode(r->left);
    return x ? x : findOneChildNode(r->right);
}

// Deleting a one-child node only splices its child into its place, so other nodes'
// child counts never change. This removes exactly the original one-child nodes.
int deleteOneChildNodes(Node*& root) {
    int deleted = 0;
    Node* t;
    while ((t = findOneChildNode(root)) != nullptr) {
        root = deleteNode(root, t->data);
        deleted++;
    }
    return deleted;
}

void kthSmallest(Node* r, int k, int& count, int& result, bool& found) {
    if (!r || found) return;
    kthSmallest(r->left, k, count, result, found);
    if (found) return;
    if (++count == k) { result = r->data; found = true; return; }
    kthSmallest(r->right, k, count, result, found);
}

int main() {
    int marks[] = {45, 25, 65, 15, 35, 55, 75, 10, 30, 40, 60, 80, 32, 33};
    int k;
    cout << "Enter k: ";
    cin >> k;

    Node* root = nullptr;
    for (int m : marks) root = insert(root, m);

    cout << "Original inorder: "; inorder(root); cout << endl;

    int mn = findMin(root), mx = findMax(root);
    double threshold = (mn + mx) / 2.0;
    cout << "Minimum: " << mn << ", Maximum: " << mx << endl;
    cout << "Threshold (avg of min & max): " << threshold << endl;
    cout << "Marks greater than threshold: "; printGreater(root, threshold); cout << endl;
    cout << "Nodes with two children: " << countTwoChildren(root) << endl;
    cout << "Longest root-to-leaf path: "; printLongestPath(root);
    cout << "  (length = " << height(root) << " edges)" << endl;
    cout << "Tree is skewed: " << (isSkewed(root) ? "Yes" : "No") << endl;

    int deleted = deleteOneChildNodes(root);
    cout << "Number of nodes deleted: " << deleted << endl;
    cout << "Final inorder: "; inorder(root); cout << endl;

    int count = 0, result = -1; bool found = false;
    kthSmallest(root, k, count, result, found);
    if (found) cout << k << "-th smallest remaining mark: " << result << endl;
    else cout << "k is larger than the number of remaining nodes" << endl;
    return 0;
}
