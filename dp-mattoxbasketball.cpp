// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> a[i];
//     }
//     vector<int> b(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> b[i];
//     }

//     // what maximum total height
//     // pick one index from first array or second array
//     // extra constraint - cannot pick two consecutive elements from an array
//     // 3 states - you take row a, row b, or nether
    
//     //dp(i, j) - the maximum sum using pairs fro [1, i] where i belings to [1, n] and j belogns to {no selection, row1, row2}

//     vector<vector<long long>> dp(n, vector<long long>(3, 0));

//     dp[0][0] = 0;
//     dp[0][1] = a[0];
//     dp[0][2] = b[0];

//     for (int i = 1; i < n; ++i) {
//         dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]});
//         dp[i][1] = max({dp[i-1][0], dp[i-1][2]}) + a[i];
//         dp[i][2] = max({dp[i-1][0], dp[i-1][1]}) + b[i];
//     }

//     cout << max({dp[n-1][0], dp[n-1][1], dp[n-1][2]}) << endl;
//     return 0;
// }


// #include <bits/stdc++.h>
// #define ll long long 
// #define MAXN 100005
// using namespace std;

// ll N, a[MAXN], b[MAXN], dp[MAXN][3];

// int main() {
//     cin >> N;
//     for (int i = 1; i <= N; ++i) cin >> a[i];
//     for (int i = 1; i <= N; ++i) cin >> b[i];
    
//     for (int i = 1; i <= N; ++i) {
//         dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]});
//         dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + a[i];
//         dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + b[i];
//     }
//     cout << max({dp[N][0], dp[N][1], dp[N][2]}) << endl;
//     return 0;
// }

#include <iostream>
using namespace std;

int main() {
    int arr[5];  // Uninitialized array (garbage values)
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";  // Undefined values
    }
    return 0;
}
