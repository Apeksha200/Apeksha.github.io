#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Step 1: DFS for topological sorting (fill stack based on finish time)
    void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& s) {
        vis[node] = 1;
        for (int neighbor : adj[node]) {
            if (!vis[neighbor]) {
                dfs(neighbor, adj, vis, s);
            }
        }
        s.push(node); // Push to stack after visiting all neighbors
    }

    // Step 2: DFS on the transposed graph
    void reverseDfs(int node, vector<vector<int>>& adjT, vector<int>& vis) {
        vis[node] = 1;
        for (int neighbor : adjT[node]) {
            if (!vis[neighbor]) {
                reverseDfs(neighbor, adjT, vis);
            }
        }
    }

    // Main function to compute number of Strongly Connected Components
    int kosaraju(int V, vector<vector<int>>& adj) {
        // ---------- Phase 1: Topological order using DFS ----------
        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, st);
            }
        }

        // ---------- Phase 2: Transpose the graph ----------
        vector<vector<int>> adjT(V);
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj[i]) {
                adjT[neighbor].push_back(i); // Reverse edge direction
            }
        }

        // ---------- Phase 3: DFS on transposed graph ----------
        fill(vis.begin(), vis.end(), 0);
        int sccCount = 0;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                sccCount++;
                reverseDfs(node, adjT, vis);
            }
        }

        return sccCount;
    }
};

int main() {
    // ✅ Static test case
    // Graph:
    // 0 → 1 → 2 → 0 (SCC1)
    // 3 → 4         (SCC2, SCC3)
    int V = 5, E = 5;
    vector<vector<int>> adj(V);

    // Directed edges
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {0};
    adj[3] = {4};
    adj[4] = {}; // no outgoing edges

    Solution obj;
    int result = obj.kosaraju(V, adj);

    cout << "Number of Strongly Connected Components: " << result << "\n";

    return 0;
}
