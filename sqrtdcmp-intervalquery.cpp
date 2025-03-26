#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, m;
    cin >> n >> m;
    vector<long long> a(n+1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    int B = sqrt(n);
    vector<int> block(n+1);
    for (int i = 1; i <= n; i++){
        block[i] = i / B; 
    }
    int maxBlock = block[n]; 
    vector<int> blockStart(maxBlock+1, n+1), blockEnd(maxBlock+1, 0);
    vector<long long> blockSum(maxBlock+1, 0);
    for (int i = 1; i <= n; i++){
        int b = block[i];
        blockStart[b] = min(blockStart[b], i);
        blockEnd[b] = max(blockEnd[b], i);
        blockSum[b] += a[i];
    }
 
    // Helper lambda to compute the sign factor.
    auto getSign = [&](int l, int j) -> int {
        int x = l ^ j;
        // If x is odd then lowest set bit is 1 => sign is -1, else +1.
        return (x & 1) ? -1 : 1;
    };
 
    while(m--){
        int l, r;
        cin >> l >> r;
        int leftBlock = block[l];
        int rightBlock = block[r];
        long long ans = 0;
 
        if(leftBlock == rightBlock){
            int sgn = getSign(l, leftBlock);
            for (int i = l; i <= r; i++){
                ans += sgn * a[i];
            }
        } else {
            int sgn = getSign(l, leftBlock);
            for (int i = l; i <= blockEnd[leftBlock]; i++){
                ans += sgn * a[i];
            }
            sgn = getSign(l, rightBlock);
            for (int i = blockStart[rightBlock]; i <= r; i++){
                ans += sgn * a[i];
            }
            for (int b = leftBlock + 1; b < rightBlock; b++){
                int sgn = getSign(l, b);
                ans += sgn * blockSum[b];
            }
        }
 
        cout << ans << "\n";
    }
    return 0;
}

/*
Interval Query (Sqrt Decomposition Ver.)
Time Limit: 1 Second
Memory Limit: 256 MB
You are asked to solve a classic problem: given an array a1, . . . , an of n elements and m intervals (l1, r1), . . . , (lm, rm)
(∀i ∈{1, . . . , m}, li ≤ri). For each interval (li, ri), find the sum of element of ali , . . . , ari.
To make sure you are really using sqrt decomposition to solve this problem, instead of findingr
i=l ai, we
ask you to findr
i=l(−1)lowbit(l⊕⌊ i
√n ⌋)ai, where ⊕is bitwise XOR, and lowbit(x) = x &−x gets the lowest
set bit in a binary number.
Input
The first line contains two integers n and m (1 ≤n, m ≤5 ×104
, √n is an integer) - the number of elements
in the array and the number of intervals.
The second line contains n integers a1, . . . an (1 ≤ai ≤109) - the elements in the array.
The last m lines describe the intervals. The i-th line contains two integers li and ri (1 ≤li ≤ri ≤n),
denoting the boundary of the i-th interval.
Output
For each interval, output a single integer denoting the sumr
i=l(−1)lowbit(l⊕⌊ i
√n ⌋)ai.
Sample Inputs

4 3
3 2 1 3
1 3
2 3
2 4
Sample Outputs
0
-3
0
*/