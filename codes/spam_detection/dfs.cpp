#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper function to perform DFS traversal
    void dfsTraverse(vector<int>& visited, int node, vector<int>& result, vector<int> adj[]) {
        visited[node] = 1;                 // Mark the node as visited
        result.push_back(node);            // Add the node to DFS traversal result
        
        for (auto neighbor : adj[node]) {  // Visit all the neighbors
            if (!visited[neighbor]) {
                dfsTraverse(visited, neighbor, result, adj); // Recursive DFS call
            }
        }
    }

    // Main function to initiate DFS traversal from node 0
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> traversalResult;
        vector<int> visited(V, 0);               // Visited vector to avoid re-visiting nodes
        
        dfsTraverse(visited, 0, traversalResult, adj);  // Start DFS from node 0
        
        return traversalResult;                  // Return the final traversal order
    }
};

// Driver code to run multiple test cases
int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        // Build the adjacency list for the graph
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u); // Since it's an undirected graph
        }

        Solution solver;
        vector<int> result = solver.dfsOfGraph(V, adj);

        // Print the DFS traversal
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
