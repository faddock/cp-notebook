#include <bits/stdc++.h>
using namespace std;
 
const long long MOD = 1000000007;
 
long long modExp(long long base, long long exponent) {
    long long result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent & 1)  // If exponent is odd
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent >>= 1;  // Divide exponent by 2
    }
    return result;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        long long n, k;
        cin >> n >> k;
        cout << modExp(n, k) << "\n";
    }
    return 0;
}