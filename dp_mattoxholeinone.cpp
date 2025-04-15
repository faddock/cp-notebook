#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> compute_dp(const vector<pair<int, int>>& items, int max_cost) {
    vector<int> dp(max_cost + 1, 0);
    for (const auto& item : items) {
        int cost = item.first;
        int value = item.second;
        for (int i = max_cost; i >= cost; --i) {
            if (dp[i - cost] + value > dp[i]) {
                dp[i] = dp[i - cost] + value;
            }
        }
    }
    for (int i = 1; i <= max_cost; ++i) {
        dp[i] = max(dp[i], dp[i-1]);
    }
    return dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int m1, m2, m3;
    cin >> m1 >> m2 >> m3;
    
    vector<pair<int, int>> upgrades_s(m1), upgrades_p(m2), upgrades_l(m3);
    for (int i = 0; i < m1; i++){
        cin >> upgrades_s[i].first >> upgrades_s[i].second;
    }
    for (int i = 0; i < m2; i++){
        cin >> upgrades_p[i].first >> upgrades_p[i].second;
    }
    for (int i = 0; i < m3; i++){
        cin >> upgrades_l[i].first >> upgrades_l[i].second;
    }
    
    auto s_dp = compute_dp(upgrades_s, n);
    auto p_dp = compute_dp(upgrades_p, n);
    auto l_dp = compute_dp(upgrades_l, n);
    
    int ans = 0;
    for (int c1 = 0; c1 <= n; ++c1) {
        for (int c2 = 0; c2 <= n - c1; ++c2) {
            int remaining = n - c1 - c2;
            if (remaining < 0) continue;
            ans = max(ans, s_dp[c1] * p_dp[c2] * l_dp[remaining]);
        }
    }
    cout << ans << "\n";
    return 0;
}

/*

B. Mattox's Hole-In-One
time limit per test1 s.
memory limit per test256 MB
Mattox wants to hit a hole-in-one in an online golf game!

He tries to calculate his chance of making a hole-in-one. He modeled this in the following way: the probability of hitting a hole-in-one is proportional to 𝑠𝑐𝑜𝑟𝑒=𝑠×𝑝×𝑙, where 𝑠 is strength, 𝑝 is precision, and 𝑙 is luck.

There are 𝑚1 upgrades Mattox can choose from that will increase his 𝑠 by 𝑣1𝑖 with a cost of 𝑐1𝑖.

There are 𝑚2 upgrades Mattox can choose from that will increase his 𝑝 by 𝑣2𝑖 with a cost of 𝑐2𝑖.

There are 𝑚3 upgrades Mattox can choose from that will increase his 𝑙 by 𝑣3𝑖 with a cost of 𝑐3𝑖.

Each upgrade can only be used ONCE.

What is the highest score Mattox can get?

Initially, 𝑠=𝑝=𝑙=0.

Input
First line: one integer 𝑛, the maximum cost

Second line: three integers 𝑚1, 𝑚2, and 𝑚3

Next 𝑚1 lines: two integers 𝑐1𝑖 and 𝑣1𝑖

Next 𝑚2 lines: two integers 𝑐2𝑖 and 𝑣2𝑖

Next 𝑚3 lines: two integers 𝑐3𝑖 and 𝑣3𝑖

1≤𝑛≤2000

1≤𝑚1,𝑚2,𝑚3≤2000

1≤𝑐≤2000,1≤𝑣≤500
Output
First line: one integer, the maximum possible score.

Examples
inputCopy
10 2 2 2
2 1
3 2
2 1
3 2
5 3
4 2
outputCopy
8
We will choose to upgrade: strength by 2 with a cost of 3; precision by 2 with a cost of 3; luck by 2 with a cost of 4. Our total cost is 10, which is less than or equal to the maximum allowed cost. Our final score is 2×2×2=8. We can show that this is the maximum possible score.

solve in c++ using dp for competitive programming*/