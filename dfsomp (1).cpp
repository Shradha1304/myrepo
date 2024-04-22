#include <iostream>
#include <vector>
#include <omp.h>
#include <queue>
#include <unordered_set>
using namespace std;

const int MAXN = 1e5;
vector<int> adj[MAXN + 5]; // adjacency list
bool visited[MAXN + 5];     // mark visited nodes

void dfs(int node) {
    visited[node] = true;
    cout << node << " "; // Print the visited node here

    // Parallel loop for visiting adjacent nodes
#pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];
        if (!visited[next_node]) {
            // Call DFS recursively for each adjacent node
            dfs(next_node);
        }
    }
}
void bfs(unordered_set<int>& visited, vector<vector<int>>& graph, int start, queue<int>& q) {
    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int s = q.front();
        q.pop();
        cout << s << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[s].size(); ++i) {
            int neighbour = graph[s][i];
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                q.push(neighbour);
            }
        }
    }
}
int main() {
    cout << "Please enter nodes and edges: ";
    int n, m; // number of nodes and edges
    cin >> n >> m;
    vector<vector<int>> graph(n);
    unordered_set<int> visited;
    queue<int> q;
    for (int i = 1; i <= m; i++) {
        int u, v; // edge between u and v
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start_node; // start node of DFS
    cout << "Enter the start node for DFS: ";
    cin >> start_node;
    dfs(start_node);
    cout<<"BFs starts";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Assuming undirected graph
    }
    cout << "Breadth-First Search (BFS) starting from node " << start_node << ": ";
    bfs(visited, graph, start_node, q);
    
    cout << endl; // Print a newline after DFS traversal
    return 0;
}

