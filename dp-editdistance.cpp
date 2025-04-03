#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    
    getline(cin, s);
    getline(cin, t);

    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for(int i=0;i<=n;i++) dp[i][0] = i;
    for(int j=0;j<=m;j++) dp[0][j] = j;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1]==t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min({dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+1});
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}

// let dp[i][j] be the minimum number of operations required to transform the first i characters of string s into the first j characters of string t.
o