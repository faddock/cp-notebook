#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1e18; 

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    long long t;
    cin >> n >> m >> k >> t;
    
    vector<int> buildings(k);
    for (int i = 0; i < k; i++) {
        cin >> buildings[i];
    }
    
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    
    for (int i = 0; i < m; i++){
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }
    
    for (int mid = 1; mid <= n; mid++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                if (dist[i][mid] < INF && dist[mid][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]);
            }
        }
    }
    
    DSU dsu(k);
    
    for (int i = 0; i < k; i++){
        for (int j = i + 1; j < k; j++){
            int u = buildings[i];
            int v = buildings[j];
            if (dist[u][v] <= t) {
                dsu.unite(i, j);
            }
        }
    }

    int root = dsu.find(0);
    for (int i = 1; i < k; i++) {
        if (dsu.find(i) != root) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
