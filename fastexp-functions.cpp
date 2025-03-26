/*Function
Time Limit: 1 Second
Memory Limit: 256 MB
A function f is defined as follows:
• f (0) = 4
• f (1) = 9
• f (2) = 5
• ∀n > 2, f (n) = 4f (n−3) + 9f (n−2) + 5f (n−1)
Given a number k (0 ≤k ≤1018), find the value of f (k). Since the value might be too large, output the
value modulo 998 244 353.
Input
The only line of input contains a single integer k (0 ≤k ≤1018), as described in the problem statement.
Output
Output the value of f (k) modulo 998 244 353.*/

#include <bits/stdc++.h>
using namespace std;


// brute force - really 
long long helper(long long num) {
    if (num == 0) {
        return 4;
    } else if (num == 1) {
        return 9;
    } else if (num == 2) {
        return 5;
    } else {
        return 4 * helper(num-3) + 9 * helper(num - 2) + 5 * helper(num-1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long k; cin >> k;
    cout << helper(k) << endl;
    return 0;
}