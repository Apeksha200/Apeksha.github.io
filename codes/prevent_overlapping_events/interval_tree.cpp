// C++ Program to implement Interval Tree
#include <iostream>
using namespace std;

// Structure to represent an interval
struct Interval {
    int low, high;
};

// Structure to represent a node in Interval Search Tree
struct Node {
    Interval *i;  
    int max;
    Node *left, *right;
};

// A utility function to create a new Interval Search Tree Node
Node * newNode(Interval i) {
    Node *temp = new Node;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = nullptr;
    return temp;
};

// A utility function to insert a new Interval Search Tree Node
// This is similar to BST Insert.  Here the low value of interval
// is used tomaintain BST property
Node *insert(Node *root, Interval i) {

    // Base case: Tree is empty, new node becomes root
    if (root == nullptr)
        return newNode(i);

    // Get low value of interval at root
    int l = root->i->low;

    // If root's low value is smaller, 
    // then new interval goes to left subtree
    if (i.low < l)
        root->left = insert(root->left, i);

    // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, i);

    // Update the max value of this ancestor if needed
    if (root->max < i.high)
        root->max = i.high;

    return root;
}

// A utility function to check if given two intervals overlap
bool isOverlapping(Interval i1, Interval i2) {
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}

// The main function that searches a given 
// interval i in a given Interval Tree.
Interval *overlapSearch(Node *root, Interval i) {

    // Base Case, tree is empty
    if (root == nullptr) return nullptr;

    // If given interval overlaps with root
    if (isOverlapping(*(root->i), i))
        return root->i;

    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != nullptr && root->left->max >= i.low)
        return overlapSearch(root->left, i);

    // Else interval can only overlap with right subtree
    return overlapSearch(root->right, i);
}

void inorder(Node *root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;
    inorder(root->right);
}

int main() {
    Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    Node *root = nullptr;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);

    cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);

    Interval x = {6, 7};

    cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
    Interval *res = overlapSearch(root, x);
    if (res == nullptr)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
    return 0;
}