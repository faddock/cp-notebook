/*
A. Circular RMQ
time limit per test1.5 seconds
memory limit per test256 megabytes
You are given circular array a0, a1, ..., an - 1. There are two types of operations with it:

inc(lf, rg, v) — this operation increases each element on the segment [lf, rg] (inclusively) by v;
rmq(lf, rg) — this operation returns minimal value on the segment [lf, rg] (inclusively).
Assume segments to be circular, so if n = 5 and lf = 3, rg = 1, it means the index sequence: 3, 4, 0, 1.

Write program to process given sequence of operations.

Input
The first line contains integer n (1 ≤ n ≤ 200000). The next line contains initial state of the array: a0, a1, ..., an - 1 ( - 106 ≤ ai ≤ 106), ai are integer. The third line contains integer m (0 ≤ m ≤ 200000), m — the number of operartons. Next m lines contain one operation each. If line contains two integer lf, rg (0 ≤ lf, rg ≤ n - 1) it means rmq operation, it contains three integers lf, rg, v (0 ≤ lf, rg ≤ n - 1; - 106 ≤ v ≤ 106) — inc operation.

Output
For each rmq operation write result for it. Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

sample input
4
1 2 3 4
4
3 0
3 0 -1
0 1
2 1

sample output
1
0
0

solve in c++ using lazy segment trees
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll INF = 1LL << 60;
 
int n;
vector<ll> seg, lazy;
 
// Build the segment tree for the array a over [l, r] at node idx.
void build(const vector<ll>& a, int idx, int l, int r) {
    if(l == r) {
        seg[idx] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(a, idx * 2, l, mid);
    build(a, idx * 2 + 1, mid + 1, r);
    seg[idx] = min(seg[idx * 2], seg[idx * 2 + 1]);
}
 
// Push lazy values down to children.
void pushDown(int idx, int l, int r) {
    if(lazy[idx] != 0) {
        int mid = (l + r) / 2;
        seg[idx * 2] += lazy[idx];
        seg[idx * 2 + 1] += lazy[idx];
        lazy[idx * 2] += lazy[idx];
        lazy[idx * 2 + 1] += lazy[idx];
        lazy[idx] = 0;
    }
}
 
// Update the segment tree in the range [ql, qr] with addition of val.
void update(int idx, int l, int r, int ql, int qr, ll val) {
    if(ql > r || qr < l)
        return;
    if(ql <= l && r <= qr) {
        seg[idx] += val;
        lazy[idx] += val;
        return;
    }
    pushDown(idx, l, r);
    int mid = (l + r) / 2;
    update(idx * 2, l, mid, ql, qr, val);
    update(idx * 2 + 1, mid + 1, r, ql, qr, val);
    seg[idx] = min(seg[idx * 2], seg[idx * 2 + 1]);
}
 
// Query the minimum value in the range [ql, qr].
ll query(int idx, int l, int r, int ql, int qr) {
    if(ql > r || qr < l)
        return INF;
    if(ql <= l && r <= qr)
        return seg[idx];
    pushDown(idx, l, r);
    int mid = (l + r) / 2;
    return min(query(idx * 2, l, mid, ql, qr),
               query(idx * 2 + 1, mid + 1, r, ql, qr));
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int m;
    cin >> m;
 
    seg.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
    build(a, 1, 0, n - 1);
 
    // Flush the rest of the current input line.
    string dummy;
    getline(cin, dummy);
 
    for (int i = 0; i < m; i++){
        string line;
        getline(cin, line);
        stringstream ss(line);
        vector<int> nums;
        int x;
        while(ss >> x) {
            nums.push_back(x);
        }
 
        // If there are two numbers: it's a rmq query.
        if(nums.size() == 2){
            int lf = nums[0], rg = nums[1];
            ll ans;
            if(lf <= rg)
                ans = query(1, 0, n - 1, lf, rg);
            else {
                // Circular query: [lf, n-1] and [0, rg]
                ll q1 = query(1, 0, n - 1, lf, n - 1);
                ll q2 = query(1, 0, n - 1, 0, rg);
                ans = min(q1, q2);
            }
            cout << ans << "\n";
        }
        // If there are three numbers: it's an inc update.
        else if(nums.size() == 3){
            int lf = nums[0], rg = nums[1], v = nums[2];
            if(lf <= rg)
                update(1, 0, n - 1, lf, rg, v);
            else {
                update(1, 0, n - 1, lf, n - 1, v);
                update(1, 0, n - 1, 0, rg, v);
            }
        }
    }
    return 0;
}
