#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, k; cin >> n >> k;
    
    ll m = min(n, k);
    ll groupSum = 0;
    
    // pre-processing
    for (ll i = 1; i <= m; ) {
        ll d = k / i;
        ll j = k / d; // max index 
        if(j > m) j = m;
        
        ll sumInterval = (i + j) * (j - i + 1) / 2;
        groupSum += d * sumInterval;
        i = j + 1;
    }
    
    ll result = m * k - groupSum;
    if(n > k)
        result += (n - k) * k;
    
    cout << result << "\n";
    return 0;
}
