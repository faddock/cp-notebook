#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    long long S;
    cin >> N >> S;
    
    vector<int> w(N), v(N);
    for(int i = 0; i < N; i++){
        cin >> w[i] >> v[i];
    }
    
    int best_idx = 0;
    for (int i = 0; i < N; i++){

        if ((long long)v[i] * w[best_idx] > (long long)v[best_idx] * w[i] ||
            ((long long)v[i] * w[best_idx] == (long long)v[best_idx] * w[i] && w[i] < w[best_idx])) {
            best_idx = i;
        }
    }
    
    int w_best = w[best_idx];
    long long v_best = v[best_idx];
    
    // Define the DP range: K = min(S, w_best^2)
    int K = (int)min(S, (long long)w_best * w_best);
    const long long NEG_INF = -1e18; // A very small number as negative infinity.
    
    vector<long long> dp(K + 1, NEG_INF);
    dp[0] = 0;
    
    // Standard unbounded knapsack DP for weights from 0 to K.
    for (int i = 0; i <= K; i++) {
        if (dp[i] < 0) continue;
        for (int j = 0; j < N; j++){
            if (i + w[j] <= K)
                dp[i + w[j]] = max(dp[i + w[j]], dp[i] + v[j]);
        }
    }
    
    long long ans = 0;
    // For each achievable weight in dp, add as many copies of the best item as possible.
    for (int x = 0; x <= K; x++){
        if (dp[x] < 0) continue;
        long long times = (S - x) / w_best; // Maximum additional copies of the best item.
        ans = max(ans, dp[x] + times * v_best);
    }
    
    cout << ans << endl;
    return 0;
}

/*

C. Mattox's Gift
time limit per test1 s
memory limit per test256 MB
You are given 𝑁 types of items (unlimited supply for each type), each having weight 𝑤𝑖 and value 𝑣𝑖.

Choose some items that have a total weight of less than or equal to 𝑆.

Maximize the total value.

Input
First line: two integers 𝑁 and 𝑆, the number of types of items, and the maximum weight allowed.

Next 𝑁 lines: two integers 𝑤𝑖 and 𝑣𝑖, the weight and the value of the 𝑖th type of item.

Limits

1≤𝑁,𝑤𝑖≤103
0≤𝑆,𝑣𝑖≤109
Output
Print a single integer, the cost of the items you choose.

Example
inputCopy
3 100
14 5
13 2
5 1
outputCopy
35
In the first example, we can choose four type-2 items and one type-3 item. The total weight is 9×4+3\time1=39≤40, making this a valid combination. The total value is 4×4+1×1=17, which is the total value we can get from this combination. We can show that this is the maximum total value we can get.

*/