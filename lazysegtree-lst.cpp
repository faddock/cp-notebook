/*
Lazy Segment Tree
Time Limit: 2 Second
Memory Limit: 2048 MB
You are given an array A with n elements (1 ≤ n ≤ 5 × 105), and all of its elements are initially 0. Write a
program that supports the following three operations:
1. Add l r v - add v to all elements in A[l . . . r]
2. Max l r - find the maximum element of A[l . . . r].
3. Sum l r - find the sum of element of A[l . . . r].
Input
The first line contains two integers n and q (1 ≤ n, q ≤ 5 × 105) - the number of elements in array A and
the number of operations.
The next q lines describe the sequence of operations. Each line starts with one of Add, Max, or Sum. If the
operation is Add, three integers l, r, and v (1 ≤ l ≤ r ≤ n, 1 ≤ v ≤ 105) follow. Otherwise two integers l and
r (1 ≤ l ≤ r ≤ n) follow.
Output
given range.
For each operation of type Max or Sum, output a single integer denoting value of the maximum element in the

sample input
3 4
Add 1 2 5
Add 2 3 6
Max 1 2
Sum 1 3

sample output
11
22

solve in c++
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
struct Node {
    ll sum;
    ll mx;
};
 
int n, q;
vector<Node> seg;
vector<ll> lazy;

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx].sum = 0;
        seg[idx].mx = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);
    seg[idx].sum = seg[2 * idx + 1].sum + seg[2 * idx + 2].sum;
    seg[idx].mx = max(seg[2 * idx + 1].mx, seg[2 * idx + 2].mx);
}
 
void pushDown(int idx, int l, int r) {
    if(lazy[idx] != 0) {
        int mid = (l + r) / 2;
        // update left child
        lazy[2 * idx + 1] += lazy[idx];
        seg[2 * idx + 1].sum += (ll)(mid - l + 1) * lazy[idx];
        seg[2 * idx + 1].mx += lazy[idx];
        // update right child
        lazy[2 * idx + 2] += lazy[idx];
        seg[2 * idx + 2].sum += (ll)(r - mid) * lazy[idx];
        seg[2 * idx + 2].mx += lazy[idx];
        lazy[idx] = 0;
    }
}
 
void update_range(int idx, int l, int r, int ql, int qr, ll val) {
    if(ql > r || qr < l)
        return;
    if(ql <= l && r <= qr) {
        seg[idx].sum += (ll)(r - l + 1) * val;
        seg[idx].mx += val;
        lazy[idx] += val;
        return;
    }
    pushDown(idx, l, r);
    int mid = (l + r) / 2;
    update_range(2 * idx + 1, l, mid, ql, qr, val);
    update_range(2 * idx + 2, mid + 1, r, ql, qr, val);
    seg[idx].sum = seg[2 * idx + 1].sum + seg[2 * idx + 2].sum;
    seg[idx].mx = max(seg[2 * idx + 1].mx, seg[2 * idx + 2].mx);
}
 
ll query_sum(int idx, int l, int r, int ql, int qr) {
    if(ql > r || qr < l)
        return 0;
    if(ql <= l && r <= qr)
        return seg[idx].sum;
    pushDown(idx, l, r);
    int mid = (l + r) / 2;
    return query_sum(2 * idx + 1, l, mid, ql, qr) +
           query_sum(2 * idx + 2, mid + 1, r, ql, qr);
}
 
ll query_max(int idx, int l, int r, int ql, int qr) {
    if(ql > r || qr < l)
        return -LLONG_MAX;
    if(ql <= l && r <= qr)
        return seg[idx].mx;
    pushDown(idx, l, r);
    int mid = (l + r) / 2;
    return max(query_max(2 * idx + 1, l, mid, ql, qr),
               query_max(2 * idx + 2, mid + 1, r, ql, qr));
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> q;
    seg.resize(4 * n);
    lazy.assign(4 * n, 0);
    build(0, 0, n - 1);
    
    while(q--){
        string op;
        cin >> op;
        int l, r;
        cin >> l >> r;
        // Convert to 0-indexed
        l--; r--;
        if(op == "Add"){
            ll v;
            cin >> v;
            update_range(0, 0, n - 1, l, r, v);
        } else if(op == "Sum"){
            cout << query_sum(0, 0, n - 1, l, r) << "\n";
        } else if(op == "Max"){
            cout << query_max(0, 0, n - 1, l, r) << "\n";
        }
    }
    return 0;
}
