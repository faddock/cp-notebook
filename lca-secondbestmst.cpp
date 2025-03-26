#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator < (const Edge& other) const {
        return w < other.w;
    }
};

struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n+1), rank(n+1, 0) {
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    
    long long mst_total = 0;
    set<pair<int, int>> mst_set;
    vector<vector<pair<int, int>>> mst_adj(n + 1);
    for (const Edge& e : edges) {
        int u = e.u, v = e.v, w = e.w;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst_total += w;
            mst_set.insert({min(u, v), max(u, v)});
            mst_adj[u].emplace_back(v, w);
            mst_adj[v].emplace_back(u, w);
        }
    }
    vector<int> parent(n + 1, -1), depth(n + 1, 0), edge_weight(n + 1, 0);
    queue<int> q;
    q.push(1);
    parent[1] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, w] : mst_adj[u]) {
            if (parent[v] == -1 && v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                edge_weight[v] = w;
                q.push(v);
            }
        }
    }
    const int LOG = 20;
    vector<vector<int>> up(LOG + 1, vector<int>(n + 1));
    vector<vector<int>> max_edge(LOG + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        if (parent[i] == -1) {
            up[0][i] = i;
            max_edge[0][i] = 0;
        } else {
            up[0][i] = parent[i];
            max_edge[0][i] = edge_weight[i];
        }
    }
    for (int k = 1; k <= LOG; ++k) {
        for (int i = 1; i <= n; ++i) {
            up[k][i] = up[k-1][up[k-1][i]];
            max_edge[k][i] = max(max_edge[k-1][i], max_edge[k-1][up[k-1][i]]);
        }
    }
    auto get_max_edge = [&](int u, int v) {
        if (u == v) return 0;
        int max_e = 0;
        if (depth[u] < depth[v]) swap(u, v);
        for (int k = LOG; k >= 0; --k) {
            if (depth[u] - (1 << k) >= depth[v]) {
                max_e = max(max_e, max_edge[k][u]);
                u = up[k][u];
            }
        }
        if (u == v) return max_e;
        for (int k = LOG; k >= 0; --k) {
            if (up[k][u] != up[k][v]) {
                max_e = max(max_e, max_edge[k][u]);
                max_e = max(max_e, max_edge[k][v]);
                u = up[k][u];
                v = up[k][v];
            }
        }
        max_e = max(max_e, max_edge[0][u]);
        max_e = max(max_e, max_edge[0][v]);
        return max_e;
    };
    long long second_best = LLONG_MAX;
    for (const Edge& e : edges) {
        int u = e.u, v = e.v, w = e.w;
        if (mst_set.count({min(u, v), max(u, v)}))
            continue;
        int current_max = get_max_edge(u, v);
        long long candidate = mst_total - current_max + w;
        if (candidate < second_best)
            second_best = candidate;
    }
    cout << second_best << "\n";
    return 0;
}