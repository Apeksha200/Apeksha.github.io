#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // A* Search Algorithm to find shortest path from S to G
    vector<int> aStar(int V, vector<vector<int>> adj[], int S, int G, vector<int>& heuristic) {
        // Min-heap: (fCost, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> gCost(V, 1e9); // g(n): distance from source to current
        vector<int> fCost(V, 1e9); // f(n) = g(n) + h(n)
        vector<bool> visited(V, false); // avoid reprocessing nodes
        vector<int> parent(V, -1); // to reconstruct path (optional)

        gCost[S] = 0;
        fCost[S] = heuristic[S];
        pq.push({fCost[S], S});

        while (!pq.empty()) {
            int node = pq.top().second;
            pq.pop();

            if (visited[node]) continue;
            visited[node] = true;

            // If goal is reached
            if (node == G) break;

            for (auto it : adj[node]) {
                int neighbor = it[0];
                int weight = it[1];

                if (!visited[neighbor]) {
                    int tentative_g = gCost[node] + weight;
                    if (tentative_g < gCost[neighbor]) {
                        gCost[neighbor] = tentative_g;
                        fCost[neighbor] = tentative_g + heuristic[neighbor];
                        parent[neighbor] = node;
                        pq.push({fCost[neighbor], neighbor});
                    }
                }
            }
        }

        // Display shortest distance
        if (gCost[G] == 1e9) {
            cout << "No path exists from " << S << " to " << G << endl;
        } else {
            cout << "Shortest distance from " << S << " to " << G << ": " << gCost[G] << endl;

            // Reconstruct path
            vector<int> path;
            for (int at = G; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << endl;
        }

        return gCost; // Optional: return all distances
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj[V];

    cout << "Enter edges in format: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // if undirected
    }

    int S, G;
    cout << "Enter source and goal node: ";
    cin >> S >> G;

    vector<int> heuristic(V);
    cout << "Enter heuristic values for all nodes:\n";
    for (int i = 0; i < V; i++) {
        cin >> heuristic[i];
    }

    Solution obj;
    obj.aStar(V, adj, S, G, heuristic);

    return 0;
}
