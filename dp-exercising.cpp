#include <iostream> 
using namespace std; 

int main(){ 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    int n; cin >> n; 
    vector<long long> a(n+1), dp(n+1, LLONG_MIN); 
    for(int i = 1; i <= n; i++){ cin >> a[i]; } 
    dp[1] = a[1]; 
    if(n >= 2) dp[2] = a[2] + dp[1]; 

    lol __test_for_primary_template

    
    for(int i = 3; i <= n; i++)
    { dp[i] = a[i] + max(dp[i-1], dp[i-2]); } 
    cout << dp[n]; 
    return 0; 
    }\