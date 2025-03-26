/*
Fast Exponentiation
Time Limit: 3 Second
Memory Limit: 256 MB
Given two numbers n and k (1 ≤ n, k ≤ 1018), output nk modulo 109 + 7.
Input
The first line contains a single integer t (1 ≤ t ≤ 105) - the number of test cases.
The following t lines describe the test cases. For each test case, the only line of input contains two integers
n and k (1 ≤ n, k ≤ 1018), as described in the problem statement.
Output
For each test case, output a single integer denoting the answer.

solution
2^10

2^2

10/2 = 5
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    const int mod = 1e9 + 7;

    while (q--) {
        long long n, k;
        cin >> n >> k;

        if (k == 0) {
            cout << 1 << endl;
            continue;
        }

        long long res = 1;
        
        while (k > 0) {
            if (k % 2 == 1) {
                res = (res * n) % mod;
            }
            n = (n * n) % mod;
            k /= 2;
        }

        cout << res << endl;
    }

    return 0;
}