/*
Fenwick Tree
Time Limit: 1.5 Second
Memory Limit: 256 MB
You are given an array a with length n (1 ≤ n ≤ 2 × 105) whose elements are all 0’s. You are then asked
to perform m (1 ≤ m ≤ 2 × 105) updates, where the i-th update adds vi to axi . After each update, output
xi-th element of the array corresponding to the Sum Fenwick tree of array a (for example, the 8th element
of the array should be a[1. . . 8] while the 6th element is a[5, 6]).
Input
The first line of input contains two integers n and m (1 ≤ n, m ≤ 2 × 105) - the number of elements of array
a and the number of updates.
For the next m lines, the i-th line contains two integers xi and vi (1 ≤ xi ≤ n, 1 ≤ vi ≤ 109), denoting that
the xi-th element in the array is added with value vi.
Output
of array a.
For each update, output an integer denoting xi-th entry of the array corresponding to the Sum Fenwick tree.

Sample Inputs
5 3
2 5
3 9
5 1

sample output
5
9
1

solve in c++
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<ll> tree(n + 1, 0);

    while(m--){
        int x;
        ll v;
        cin >> x >> v;
        for (int i = x; i <= n; i += (i & -i)) {
            tree[i] += v;
        }
        cout << tree[x] << "\n";
    }
    
    return 0;
}
