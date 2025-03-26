/*
Shopping
Time Limit: 1 Second
Memory Limit: 2048 MB
LetianPie loves buying new stuffs so he goes shopping almost everyday! However, he soon realized that
he will run out of money if he keeps doing this, so he decided to control the amount of money he spends
everyday. Specifically, every morning LetianPie will write n checks and place them in a line. He will then
pick two integers l and r (1 ≤ l ≤ r ≤ n) and grab all checks in range [l, r] for shopping today. The only
issue with this is that he has to pay the exact amount of the item he buys because there is no way the shop
can make changes for his checks! To decide the values of l and r he should choose each morning, he asks you
to help him find out the smallest amount that he can’t pay with checks in the range [l, r].
Input
The first line of input contains two integers n and q (1 ≤ n, q ≤ 105) - the number of checks LetianPie wrote
and the number of queries.
The next line contains n integers a1, . . . , an (1 ≤ ai ≤ 109) denoting the value of each check.
The next q lines describe the queries. Each line contains two integers l and r (1 ≤ l ≤ r ≤ n), meaning that
LetianPie will grab the checks in the range [l, r]. All queries are independent.
Output
For each query, output a single integer denoting the minimum amount of money LetianPie cannot pay with
the checks he grabs.

sample input
5 3
1 5 2 4 3
1 2
1 5
3 4

sample output 
2
16
1

solve in c++ using segment trees*/

#include <bits/stdc++.h>
using namespace std;
struct Node {
    vector<long long> v;
    vector<long long> ps;
};

vector<long long> arr;
vector<Node> seg(4*100005);
void build(int idx, int l, int r){
    if(l==r){
        seg[idx].v = {arr[l-1]};
        seg[idx].ps = {arr[l-1]};
        return;
    }
    int mid = (l+r)/2;
    build(idx*2,l,mid);
    build(idx*2+1,mid+1,r);
    vector<long long> tmp(seg[idx*2].v.size()+seg[idx*2+1].v.size());
    merge(seg[idx*2].v.begin(), seg[idx*2].v.end(), seg[idx*2+1].v.begin(), seg[idx*2+1].v.end(), tmp.begin());
    seg[idx].v = tmp;
    seg[idx].ps.resize(tmp.size());
    seg[idx].ps[0] = tmp[0];
    for (size_t i=1;i<tmp.size();i++) seg[idx].ps[i] = seg[idx].ps[i-1] + tmp[i];
}
Node query(int idx, int l, int r, int ql, int qr){
    if(ql>r || qr<l) return Node();
    if(ql<=l && r<=qr) return seg[idx];
    int mid = (l+r)/2;
    Node left = query(idx*2,l,mid,ql,qr), right = query(idx*2+1,mid+1,r,ql,qr);
    if(left.v.empty()) return right;
    if(right.v.empty()) return left;
    Node res;
    res.v.resize(left.v.size()+right.v.size());
    merge(left.v.begin(), left.v.end(), right.v.begin(), right.v.end(), res.v.begin());
    res.ps.resize(res.v.size());
    res.ps[0] = res.v[0];
    for(size_t i=1;i<res.v.size();i++) res.ps[i] = res.ps[i-1] + res.v[i];
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    arr.resize(n);
    for (int i=0;i<n;i++) cin >> arr[i];
    build(1,1,n);
    for (int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        Node res = query(1,1,n,l,r);
        long long cur = 1;
        for(auto v: res.v){
            if(v>cur) break;
            cur += v;
        }
        cout << cur << "\n";
    }
    return 0;
}
