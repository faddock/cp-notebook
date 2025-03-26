#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    // Precompute all valid masks for a row of length m.
    // A mask is valid if it does not have two consecutive 1s.
    vector<int> valid;
    vector<int> ones(1 << m, 0);
    for (int mask = 0; mask < (1 << m); mask++){
        if (mask & (mask << 1)) continue; // adjacent kings horizontally: invalid.
        valid.push_back(mask);
        ones[mask] = __builtin_popcount(mask);
    }
    
    int states = valid.size();
    // dp[row][state_index][placedKings] = ways to fill rows 0..row with given last row mask.
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(states, vector<long long>(k+1, 0)));
    
    // Base case: first row.
    for (int i = 0; i < states; i++){
        int cnt = ones[ valid[i] ];
        if (cnt <= k)
            dp[0][i][cnt] = 1;
    }
    
    // Process subsequent rows.
    for (int row = 1; row < n; row++){
        for (int i = 0; i < states; i++){
            int cur = valid[i];
            int curCount = ones[cur];
            for (int j = 0; j < states; j++){
                int prev = valid[j];

                if (cur & prev) continue;
                if (cur & (prev << 1)) continue;
                if (cur & (prev >> 1)) continue;

                for (int c = 0; c <= k - curCount; c++){
                    dp[row][i][c + curCount] += dp[row - 1][j][c];
                }
            }
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < states; i++){
        ans += dp[n - 1][i][k];
    }
    cout << ans << "\n";
    return 0;
}
