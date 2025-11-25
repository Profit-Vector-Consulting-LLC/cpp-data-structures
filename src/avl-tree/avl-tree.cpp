#include <iostream>
#include <vector>
#include <queue>
#include <initializer_list>
using namespace std;

struct Node {
    int key;
    Node *left, *right, *parent;
    int height;
    Node(int k, Node* p=nullptr): key(k), left(nullptr), right(nullptr), parent(p), height(1) {}
};

static int h(Node* n) { return n ? n->height : 0; }
static int bf(Node* n) { return n ? h(n->left) - h(n->right) : 0; }
static void update(Node* n) {
    if (n) n->height = 1 + max(h(n->left), h(n->right));
}

// Left rotate at x:
//      x                 y
//       \               / \
//        y     ->      x   T3
//       / \             \
//     T2  T3            T2
static Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotate
    y->left = x;
    x->right = T2;

    // Parents
    y->parent = x->parent;
    x->parent = y;
    if (T2) T2->parent = x;

    // Heights
    update(x);
    update(y);
    return y;
}

// Right rotate at y:
//        y              x
//       /              / \
//      x      ->      T1  y
//     / \                /
//   T1  T2              T2
static Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotate
    x->right = y;
    y->left = T2;

    // Parents
    x->parent = y->parent;
    y->parent = x;
    if (T2) T2->parent = y;

    // Heights
    update(y);
    update(x);
    return x;
}

static Node* rebalance(Node* node) {
    update(node);
    int balance = bf(node);

    // LL
    if (balance > 1 && bf(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (balance > 1 && bf(node->left) < 0) {
        node->left = leftRotate(node->left);
        if (node->left) node->left->parent = node;
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && bf(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (balance < -1 && bf(node->right) > 0) {
        node->right = rightRotate(node->right);
        if (node->right) node->right->parent = node;
        return leftRotate(node);
    }

    return node;
}

static Node* insertRec(Node* root, int key, Node* parent=nullptr) {
    if (!root) return new Node(key, parent);
    if (key < root->key) {
        root->left = insertRec(root->left, key, root);
    } else if (key > root->key) {
        root->right = insertRec(root->right, key, root);
    } else {
        // no duplicates for this demo
        return root;
    }
    Node* newRoot = rebalance(root);
    return newRoot;
}

static Node* minNode(Node* n) {
    while (n && n->left) n = n->left;
    return n;
}

static Node* deleteRec(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteRec(root->left, key);
        if (root->left) root->left->parent = root;
    } else if (key > root->key) {
        root->right = deleteRec(root->right, key);
        if (root->right) root->right->parent = root;
    } else {
        // node to delete
        if (!root->left || !root->right) {
            Node* child = root->left ? root->left : root->right;
            if (!child) {
                // leaf
                delete root;
                return nullptr;
            } else {
                // one child
                child->parent = root->parent;
                Node* old = root;
                root = child;
                delete old;
            }
        } else {
            // two children: replace with inorder successor
            Node* succ = minNode(root->right);
            root->key = succ->key;
            root->right = deleteRec(root->right, succ->key);
            if (root->right) root->right->parent = root;
        }
    }
    return rebalance(root);
}

// Print each level on its own line; each node as "parent:node"
static void printLevels(Node* root) {
    if (!root) { cout << "(empty)\n"; return; }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        size_t sz = q.size();
        for (size_t i = 0; i < sz; ++i) {
            Node* cur = q.front(); q.pop();
            if (cur->parent) cout << cur->parent->key << ":" << cur->key;
            else cout << "-:" << cur->key; // root
            if (i + 1 < sz) cout << "  ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << "\n";
    }
    cout << "\n";
}

static Node* build(const initializer_list<int>& vals) {
    Node* root = nullptr;
    for (int v : vals) root = insertRec(root, v);
    return root;
}

static void demoInsert(const initializer_list<int>& vals, const string& title) {
    cout << "=== " << title << " ===\n";
    Node* root = nullptr;
    for (int v : vals) {
        cout << "Insert " << v << ":\n";
        root = insertRec(root, v);
        printLevels(root);
    }
}

static void demoDelete(initializer_list<int> initVals, initializer_list<int> dels, const string& title) {
    cout << "=== " << title << " ===\n";
    Node* root = build(initVals);
    cout << "Initial tree:\n";
    printLevels(root);
    for (int d : dels) {
        cout << "Delete " << d << ":\n";
        root = deleteRec(root, d);
        printLevels(root);
    }
}

int main() {
    // INSERTION demos to show all four rotations:

    // LL rotation: insert 30, 20, 10 (unbalanced left-left at 30)
    demoInsert({30, 20, 10}, "Insertion LL case (right rotation)");

    // RR rotation: insert 10, 20, 30 (unbalanced right-right at 10)
    demoInsert({10, 20, 30}, "Insertion RR case (left rotation)");

    // LR rotation: insert 30, 10, 20 (left-right double rotation at 30)
    demoInsert({30, 10, 20}, "Insertion LR case (left-right rotation)");

    // RL rotation: insert 10, 30, 20 (right-left double rotation at 10)
    demoInsert({10, 30, 20}, "Insertion RL case (right-left rotation)");

    // DELETION demos that trigger rebalancing:
    // Classic AVL set; deletions often trigger rotations.
    demoDelete(
        {9,5,10,0,6,11,-1,1,2},   // initial values
        {10, 5},                  // deletions (typically cause rebalances)
        "Deletion rebalancing examples"
    );

    return 0;
}

