#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<vector<int>> adjList(N + 1); // Using 1-based indexing
    for (int i = 0; i < M; ++i) {
        int u, v; 
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    vector<int> depth(N + 1, -1);
    vector<int> colors(N + 1, 0);
    
    auto dfs = [&](int u, int parent, auto&& dfs) -> void {
        depth[u] = (parent == -1) ? 0 : (depth[parent] + 1);
        colors[u] = (depth[u] % K) + 1;
        for (int v : adjList[u]) {
            if (depth[v] == -1) {
                dfs(v, u, dfs); // Recursive call
            }
        }
    };
    
    for (int u = 1; u <= N; ++u) {
        if (depth[u] == -1) {
            dfs(u, -1, dfs);
        }
    }
    
    // Check if any adjacent nodes have the same color
    bool valid = true;
    for (int u = 1; u <= N; ++u) {
        for (int v : adjList[u]) {
            if (colors[u] == colors[v]) {
                valid = false;
                break;
            }
        }
        if (!valid) break;
    }
    
    if (!valid) {
        cout << "-1\n";
    } else {
        for (int i = 1; i <= N; ++i) {
            cout << colors[i] << '\n';
        }
    }
    
    return 0;
}