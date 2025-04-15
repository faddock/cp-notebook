#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    vector<int> a(n), v(n);

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> v[i];

    vector<int> dp(t + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = t; j >= a[i]; --j) {
            dp[j] = max(dp[j], dp[j - a[i]] + v[i]);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}
