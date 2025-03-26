#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<vector<int>> reversed_adj(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        reversed_adj[v].push_back(u);
    }

    vector<bool> visited(n, false);
    stack<int> order;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            stack<pair<int, bool>> s;
            s.push({i, false});
            while (!s.empty()) {
                auto [u, processed] = s.top();
                s.pop();
                if (processed) {
                    order.push(u);
                    continue;
                }
                if (visited[u]) continue;
                visited[u] = true;
                s.push({u, true});
                for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                    int v = *it;
                    if (!visited[v]) {
                        s.push({v, false});
                    }
                }
            }
        }
    }

    vector<int> component(n, -1);
    int current_component = 0;

    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (component[u] == -1) {
            stack<int> s;
            s.push(u);
            component[u] = current_component;
            while (!s.empty()) {
                int v = s.top();
                s.pop();
                for (int w : reversed_adj[v]) {
                    if (component[w] == -1) {
                        component[w] = current_component;
                        s.push(w);
                    }
                }
            }
            current_component++;
        }
    }

    vector<int> in_degree(current_component, 0);
    unordered_set<long long> edge_set;

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            int a = component[u];
            int b = component[v];
            if (a != b) {
                long long key = (long long)a * 1000000000LL + b;
                if (edge_set.find(key) == edge_set.end()) {
                    edge_set.insert(key);
                    in_degree[b]++;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < current_component; i++) {
        if (in_degree[i] == 0) {
            result++;
        }
    }

    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}