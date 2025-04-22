#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, m1, m2, m3; cin >> N >> m1 >> m2 >> m3;
    vector<int> dp1(N+1, 0);
    for(int i = 0; i < m1; i++){
        int c, v; cin >> c >> v;
        for(int b = N; b >= c; b--){
            if(dp1[b - c] + v > dp1[b]) dp1[b] = dp1[b - c] + v;
        }
    }

    vector<int> dp2(N+1, 0);
    for(int i = 0; i < m2; i++){
        int c, v; cin >> c >> v;
        for(int b = N; b >= c; b--){
            if(dp2[b - c] + v > dp2[b]) dp2[b] = dp2[b - c] + v;
        }
    }

    vector<int> dp3(N+1, 0);
    for(int i = 0; i < m3; i++){
        int c, v; cin >> c >> v;
        for(int b = N; b >= c; b--){
            if(dp3[b - c] + v > dp3[b]) dp3[b] = dp3[b - c] + v;
        }
    }

    vector<int> best3(N+1, 0);
    best3[0] = dp3[0];
    for(int c = 1; c <= N; c++){
        best3[c] = best3[c - 1] > dp3[c] ? best3[c - 1] : dp3[c];
    }

    ll answer = 0;
    for(int c1 = 0; c1 <= N; c1++){
        if(dp1[c1] == 0) continue;
        for(int c2 = 0; c2 + c1 <= N; c2++){
            if(dp2[c2] == 0) continue;
            int rem = N - c1 - c2;
            int s = dp1[c1], p = dp2[c2], l = best3[rem];
            if(l == 0) continue;
            ll prod = (ll)s * p * l;
            if(prod > answer) answer = prod;
        }
    }

    cout << answer << endl;
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