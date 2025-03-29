/*
Shopping
Time Limit: 1 Second
Memory Limit: 2048 MB
LetianPie loves buying new stuffs so he goes shopping almost everyday! However, he soon realized that
he will run out of money if he keeps doing this, so he decided to control the amount of money he spends
everyday. Specifically, every morning LetianPie will write n checks and place them in a line. He will then
pick two integers l and r (1 ≤ l ≤ r ≤ n) and grab all checks in range [l, r] for shopping today. The only
issue with this is that he has to pay the exact amount of the item he buys because there is no way the shop
can make changes for his checks! To decide the values of l and r he should choose each morning, he asks you
to help him find out the smallest amount that he can’t pay with checks in the range [l, r].
Input
The first line of input contains two integers n and q (1 ≤ n, q ≤ 105) - the number of checks LetianPie wrote
and the number of queries.
The next line contains n integers a1, . . . , an (1 ≤ ai ≤ 109) denoting the value of each check.
The next q lines describe the queries. Each line contains two integers l and r (1 ≤ l ≤ r ≤ n), meaning that
LetianPie will grab the checks in the range [l, r]. All queries are independent.
Output
For each query, output a single integer denoting the minimum amount of money LetianPie cannot pay with
the checks he grabs.

sample input
5 3
1 5 2 4 3
1 2
1 5
3 4

sample output 
2
16
1

solve in c++ using segment trees*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; // Convert to 0-indexed
        
        // Get values in the range
        vector<ll> range_values(arr.begin() + l, arr.begin() + r);
        sort(range_values.begin(), range_values.end());
        
        ll current_sum = 0;
        for (ll val : range_values) {
            if (val > current_sum + 1)
                break;
            current_sum += val;
        }
        
        cout << current_sum + 1 << "\n";
    }
    
    return 0;
}