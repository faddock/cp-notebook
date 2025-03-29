#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> dp;
    vector<int> prev(n, -1);
    vector<int> pos;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i], 
                            [&](int pos, int val) { return a[pos] < val; });
        
        if (it == dp.end()) {
            if (!dp.empty()) {
                prev[i] = dp.back();
            }
            dp.push_back(i);
            pos.push_back(i);
        } else {
            if (it != dp.begin()) {
                prev[i] = dp[it - dp.begin() - 1];
            }
            *it = i;
            pos[it - dp.begin()] = i;
        }
    }

    cout << dp.size() << endl;
    vector<int> lis;
    int curr = dp.back();
    while (curr != -1) {
        lis.push_back(a[curr]);
        curr = prev[curr];
    }
    reverse(lis.begin(), lis.end());
    
    for (int i = 0; i < lis.size(); i++) {
        cout << lis[i];
        if (i < lis.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    return 0;
}

/*

Longest Increasing Subsequence

Time Limit: 1 Second

Memory Limit: 256 MB

Given an array a1, . . . , an of n elements, find out the longest increasing subsequence of the array. A subse-

quence of an array is obtained by deleting zero or more elements from the array. An increasing subsequence

is a subsequence such that each element is strictly greater than the previous element in the sequence.

Input

The first line of input contains a single integer n (1 ≤ n ≤ 2 × 105) - number of elements in the array.

The second line contains n integers a1, . . . , an (0 ≤ ai ≤ 105) - elements of the array.

Output

In the first line, output a single integer denoting the length of the longest increasing subsequence of the

array.

In the second line, output the longest increasing subsequence. If there is more than one answer, you can

output any of them

sample input

5

3 2 1 4 5

sample output

3

1 4 5

solve in c++ for competitive programming
*/
