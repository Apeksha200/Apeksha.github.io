#include <bits/stdc++.h>
using namespace std;

// Node class for Huffman tree
class Node {
public:
    int data;
    Node *left, *right;
    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
    Node(int data, Node *left, Node *right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

// Comparator for priority queue (min-heap based on frequency)
struct compare {
    bool operator()(Node *n1, Node *n2) {
        return n1->data > n2->data;
    }
};

class Solution {
public:
    // Helper function to perform DFS traversal and generate Huffman codes
    void traversal(Node *root, string code, vector<string> &ans) {
        // If it's a leaf node, push the generated code
        if (!root->left && !root->right) {
            ans.push_back(code);
            return;
        }

        // Recur for left with '0' and right with '1'
        if (root->left) traversal(root->left, code + "0", ans);
        if (root->right) traversal(root->right, code + "1", ans);
    }

    // Function to generate Huffman Codes
    vector<string> huffmanCodes(string S, vector<int> f, int N) {
        priority_queue<Node*, vector<Node*>, compare> pq;
        vector<string> res;

        // Create a leaf node for each character and push into the min-heap
        for (int i = 0; i < N; i++) {
            pq.push(new Node(f[i]));
        }

        // Build the Huffman tree
        while (pq.size() > 1) {
            Node *left = pq.top(); pq.pop();
            Node *right = pq.top(); pq.pop();

            // Combine the two smallest nodes
            Node *merged = new Node(left->data + right->data, left, right);
            pq.push(merged);
        }

        // Traverse the built Huffman tree to get codes
        traversal(pq.top(), "", res);
        return res;
    }
};

// Driver code
int main() {
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int N = S.length();
        vector<int> f(N);

        for (int i = 0; i < N; i++) {
            cin >> f[i];
        }

        Solution ob;
        vector<string> ans = ob.huffmanCodes(S, f, N);
        for (const auto &code : ans) {
            cout << code << " ";
        }
        cout << "\n";
    }
    return 0;
}
