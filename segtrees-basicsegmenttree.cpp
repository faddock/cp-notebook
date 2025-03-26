/*
Basic Segment Tree
Time Limit: 1 Second
Memory Limit: 2048 MB
You are given an array A with n elements (1 ≤ n ≤ 5 × 105), and all of its elements are initially 0. Write a
program that supports the following three operations:
1. Add x v - add v to x-th element of A.
2. Set x v - set x-th element to v.
3. Max l r - find the maximum element of A[l . . . r].
Input
The first line contains two integers n and q (1 ≤ n, q ≤ 5 × 105) - the number of elements in array A and
the number of operations.
The next q lines describe the sequence of operations. Each line starts with one of Add, Set, or Max. If the
operation is Add or Set, two integers x and v (1 ≤ x ≤ n, 1 ≤ v ≤ 105) follow. Otherwise two integers l and
r (1 ≤ l ≤ r ≤ n) follow.
Output
range.
For each operation of type Max, output a single integer denoting value of the maximum element in the given

sample input
3 4
Add 1 2
Max 1 3
Set 2 5
Max 1 3

sample output
2
5
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    vector<long long> seg(2 * n, 0);
    
    auto update = [&](int idx, long long val) {
        idx += n;
        seg[idx] = val;
        for(idx /= 2; idx > 0; idx /= 2)
            seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
    };
    

    auto add = [&](int idx, long long val) {
        idx += n;
        seg[idx] += val;
        for(idx /= 2; idx > 0; idx /= 2)
            seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
    };
    
    auto query = [&](int l, int r) -> long long {
        long long res = 0;
        l += n;
        r += n;
        while(l <= r){
            if(l % 2 == 1){
                res = max(res, seg[l]);
                l++;
            }
            if(r % 2 == 0){
                res = max(res, seg[r]);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return res;
    };
    
    for(int i = 0; i < q; i++){
        string op;
        cin >> op;
        if(op == "Add"){
            int x;
            long long v;
            cin >> x >> v;
            x--;
            add(x, v);
        }
        else if(op == "Set"){
            int x;
            long long v;
            cin >> x >> v;
            x--;
            update(x, v);
        }
        else if(op == "Max"){
            int l, r;
            cin >> l >> r;
            l--; r--; 
            cout << query(l, r) << "\n";
        }
    }
    return 0;
}