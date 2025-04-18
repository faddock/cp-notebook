#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;

    while(T--){
        int k, d; string my_str;
        cin >> k >> d >> my_str;
        int n = my_str.size();
        vector<int> prefix(n+1, 0);
        for(int i = 0; i < n; i++){
            prefix[i+1] = prefix[i] + (my_str[i] == '0');
        }
        vector<int> cost(n, k+1);
        for(int i = 0; i + d <= n; i++){
            cost[i] = prefix[i+d] - prefix[i];
        }
        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
        for(int i = n - 1; i >= 0; i--){
            for(int r = 0; r <= k; r++){
                int skip = dp[i+1][r];
                int take = 0;
                if(cost[i] <= r){
                    take = 1 + dp[i+d][r - cost[i]];
                }
                dp[i][r] = skip > take ? skip : take;
            }
        }
        cout << dp[0][k] << endl;
    }
    return 0;
}