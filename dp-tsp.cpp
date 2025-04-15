#include <bits/stdc++.h>
using namespace std;

static const int INF = 1000000000;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    // dist[i][j] will hold the shortest distance from i to j
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for(int i = 0; i < n; i++){
        dist[i][i] = 0;
    }

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        // convert to 0-based
        --u; 
        --v;
        // bidirectional roads
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // Floyd-Warshall for all-pairs shortest paths
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(dist[i][k] == INF) continue;
            for(int j = 0; j < n; j++){
                if(dist[k][j] == INF) continue;
                int nd = dist[i][k] + dist[k][j];
                if(nd < dist[i][j]){
                    dist[i][j] = nd;
                }
            }
        }
    }

    // DP array: dp[mask][pos]
    // dp[mask][pos] = minimum distance to have visited
    // the set of cities in "mask", ending at city "pos"
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    // Initialize dp for single-city visits
    for(int i = 0; i < n; i++){
        dp[1 << i][i] = 0;
    }

    // Build up answers for all subsets
    for(int mask = 0; mask < (1 << n); mask++){
        for(int pos = 0; pos < n; pos++){
            int curDist = dp[mask][pos];
            if(curDist == INF) continue;
            // Try to go to a new city "nxt" not in 'mask'
            for(int nxt = 0; nxt < n; nxt++){
                if((mask & (1 << nxt)) == 0 && dist[pos][nxt] < INF){
                    int newMask = mask | (1 << nxt);
                    int cost = curDist + dist[pos][nxt];
                    if(cost < dp[newMask][nxt]){
                        dp[newMask][nxt] = cost;
                    }
                }
            }
        }
    }

    // Final answer: minimum among dp[(1<<n)-1][pos], for pos in [0..n-1]
    int fullMask = (1 << n) - 1;
    int ans = INF;
    for(int pos = 0; pos < n; pos++){
        ans = min(ans, dp[fullMask][pos]);
    }
    cout << ans << "\n";
    return 0;
}