/*
Speed Limit!
Time Limit: 1 Second
Memory Limit: 2048 MB
LetianPie loves traveling so he drives his car to explore new cities every weekend. As he spent a lot of time
driving, he discovered an annoying fact about the interstates – the speed limit changes frequently. To avoid
getting into trouble by over-speeding, he has to slow down his speed whenever the speed limit decreases,
which increases his fuel consumption. To count the number of times he needs to change his speed, he asks
you for help. Specifically, there will be three types of events:
• + l r k: the speed limit between exits l and r (inclusive) is updated to k mph. The values of k
among all events are distinct.
• ? l r: LetianPie asks you the number of times he would need to change his speed if he enters the
interstate at exit l and leaves at exit r.
Assume that LetianPie will drive exactly at the speed limit (so he will increase his speed if the speed limit
increases), and the initial speed limit for the interstate is ∞anywhere.
Input
The first line of input contains two integers n and q (2 ≤n ≤109, 1 ≤q ≤105) - the number of exits on the
interstate and the number of events.
The next q lines describe the events. Each line starts with either +, or ?. If the symbol is +, it will be
followed by three integers l, r, and k (1 ≤l < r ≤n, 1 ≤k ≤109). Otherwise the symbol will be followed
by two integers l and r (1 ≤l < r ≤n).
Output
For each query, output a single integer denoting the number of times LetianPie will need to adjust his speed.

sample input
4 4
+ 1 2 5
? 2 3
+ 2 3 6
? 1 4

sample output 
0
2

Note
• The first event updates the speed limit between exit 1 and 2 to 5 mph.
• In the second event, LetianPie enters at exit 2 and leaves at exit 3, and the speed limit is ∞all over
the trip.
• The third event updates the speed limit between exit 2 and 3 to 6 mph.
• In the last event, LetianPie enters at exit 1 and leaves at exit 4. His initial speed will be 5 mph,
increasing to 6 mph at exit 2, and reaching ∞mph at exit 3.

solve in c++ using segment trees 
*/

#include <bits/stdc++.h>
using namespace std;
const long long INF = 1000000001LL;
struct Event { char type; long long l, r, k; };
struct Seg { long long L, R, lval, rval, assign; int cnt; bool lazy; };
int M;
vector<pair<long long, long long>> segs;
vector<Seg> tree;
void buildTree(int idx, int s, int e) {
    if(s==e){
        tree[idx].L = segs[s].first;
        tree[idx].R = segs[s].second;
        tree[idx].lval = INF;
        tree[idx].rval = INF;
        tree[idx].cnt = 0;
        tree[idx].lazy = false;
        return;
    }
    int mid = (s+e)/2;
    buildTree(idx*2, s, mid);
    buildTree(idx*2+1, mid+1, e);
    tree[idx].L = tree[idx*2].L;
    tree[idx].R = tree[idx*2+1].R;
    tree[idx].lval = tree[idx*2].lval;
    tree[idx].rval = tree[idx*2+1].rval;
    tree[idx].cnt = tree[idx*2].cnt + tree[idx*2+1].cnt + (tree[idx*2].rval != tree[idx*2+1].lval);
    tree[idx].lazy = false;
}
void apply(int idx, long long val) {
    tree[idx].lval = val;
    tree[idx].rval = val;
    tree[idx].cnt = 0;
    tree[idx].lazy = true;
    tree[idx].assign = val;
}
void pushDown(int idx) {
    if(tree[idx].lazy){
        apply(idx*2, tree[idx].assign);
        apply(idx*2+1, tree[idx].assign);
        tree[idx].lazy = false;
    }
}
void updateTree(int idx, int s, int e, long long ql, long long qr, long long val) {
    if(tree[idx].R < ql || tree[idx].L > qr)return;
    if(ql <= tree[idx].L && tree[idx].R <= qr){
        apply(idx, val);
        return;
    }
    pushDown(idx);
    int mid = (s+e)/2;
    updateTree(idx*2, s, mid, ql, qr, val);
    updateTree(idx*2+1, mid+1, e, ql, qr, val);
    tree[idx].lval = tree[idx*2].lval;
    tree[idx].rval = tree[idx*2+1].rval;
    tree[idx].cnt = tree[idx*2].cnt + tree[idx*2+1].cnt + (tree[idx*2].rval != tree[idx*2+1].lval);
}
Seg queryTree(int idx, int s, int e, long long ql, long long qr) {
    if(tree[idx].R < ql || tree[idx].L > qr){
        Seg res; res.lval = -1; return res;
    }
    if(ql <= tree[idx].L && tree[idx].R <= qr)return tree[idx];
    pushDown(idx);
    int mid = (s+e)/2;
    Seg leftRes = queryTree(idx*2, s, mid, ql, qr);
    Seg rightRes = queryTree(idx*2+1, mid+1, e, ql, qr);
    if(leftRes.lval == -1)return rightRes;
    if(rightRes.lval == -1)return leftRes;
    Seg res;
    res.L = leftRes.L;
    res.R = rightRes.R;
    res.lval = leftRes.lval;
    res.rval = rightRes.rval;
    res.cnt = leftRes.cnt + rightRes.cnt + (leftRes.rval != rightRes.lval);
    res.lazy = false;
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; long long n;
    cin >> n >> q;
    vector<Event> events(q);
    vector<long long> coords;
    coords.push_back(1);
    coords.push_back(n-1);
    for (int i=0;i<q;i++){
        cin >> events[i].type;
        if(events[i].type=='+'){
            cin >> events[i].l >> events[i].r >> events[i].k;
            long long L = events[i].l, R = events[i].r - 1;
            coords.push_back(L);
            coords.push_back(R);
        } else {
            cin >> events[i].l >> events[i].r;
            long long L = events[i].l, R = events[i].r - 1;
            coords.push_back(L);
            coords.push_back(R);
        }
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    long long cur = 1;
    for(auto x: coords){
        if(cur < x) segs.push_back({cur, x-1});
        segs.push_back({x, x});
        cur = x+1;
    }
    if(cur <= n-1) segs.push_back({cur, n-1});
    M = segs.size();
    tree.resize(4 * M);
    buildTree(1, 0, M-1);
    for (int i=0;i<q;i++){
        if(events[i].type=='+'){
            long long L = events[i].l, R = events[i].r - 1;
            updateTree(1, 0, M-1, L, R, events[i].k);
        } else {
            long long L = events[i].l, R = events[i].r - 1;
            Seg ans = queryTree(1, 0, M-1, L, R);
            cout << ans.cnt << "\n";
        }
    }
    return 0;
}