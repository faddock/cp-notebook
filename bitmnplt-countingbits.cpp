#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long sum_bits(long long n) {
    if (n < 0) return 0;
    long long total = 0;
    for (int k = 0; (1ULL << k) <= n; ++k) {
        unsigned long long two_k = 1ULL << k;
        unsigned long long two_k_plus_1 = two_k << 1;
        unsigned long long cycles = (n + 1) / two_k_plus_1;
        unsigned long long remainder = (n + 1) % two_k_plus_1;
        unsigned long long cnt = cycles * two_k;
        if (remainder > two_k) {
            cnt += remainder - two_k;
        }
        total = (total + cnt) % MOD;
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long l, r;
        cin >> l >> r;
        long long a = sum_bits(r);
        long long b = sum_bits(l - 1);
        long long ans = (a - b) % MOD;
        if (ans < 0) ans += MOD;
        cout << ans << '\n';
    }
    return 0;
}


// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);

//     int q; cin >> q;
//     while (q--) {
//         int l, r;
//         cin >> l >> r;
//         int sum = 0;
//         for (int i = l; i <= r; i++) {
//             sum += __builtin_popcount(i);
//         }
//         cout << sum << endl;
//     }
    
//     return 0;
// }