/*
ISR (Hard Version)
Time Limit: 1 Second
Memory Limit: 2048 MB
If you have seen the normal version of this problem in this class before, the only difference
between the two versions is that you need to answer a series of queries in this version.
After his last visit to ISR Dining Center, LetianPie found the food was so good that he decided to go to ISR
for dinner everyday. After several visits, LetianPie discovered that ISR actually provides even more types of
food, but some of them are only available on certain weekdays. In specific, ISR provides n different kinds of
food in total, with i-th kind of food served on the i-th table, and all tables are arranged in a line. On the
i-th day, only tables in [li, ri] are open to customers.
In ISR, each person can choose to get in line at i-th table, and leave the line at j-th table (i ≤ j), grabbing
all kinds of food between i-th table and j-th table (inclusive). Each person can only get in line once during
one visit.
LetianPie has already assigned each kind of food an long longeger value denoting how much he likes this kind of
food. In specific, the i-th kind of food is assigned with value ai (−105 ≤ ai ≤ 105), where a positive value
indicates that LetianPie likes this kind of food, and vice versa. Moreover, he has also known which tables
will be open in the next m days from Illinois App. The happiness LetianPie gains from each dinner is the
sum of values assigned to the foods he picks. Now LetianPie is wondering the maximum total happiness he
can gain if he visits ISR in the next m days, and he chooses the starting and ending tables optimally. Since
he is too hungry to think about it, he asks you to help him out.
Input
The first line contains two long longeger n and m (1 ≤ n, m ≤ 10^5) - the number of foods provided by ISR and the
number of days LetianPie is going to ISR for dinner.
The second line contains n long longeger a1, . . . , an (−10^5 ≤ ai ≤ 10^5) - how much LetianPie likes each kind of
food.
The next m lines describe the food offered by ISR in the next m days. Each line contains two long longegers l and
r (1 ≤ l ≤ r ≤ n), as described in the problem statement.
Output
Output a single long longeger denoting the maximum total happiness LetianPie can gain from the dinners

sample input
5 3
3 -2 -1 4 0
2 3
1 5
1 3

sample output
7

solve in c++ using segment trees
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum, pref, suff, ans;
};

vector<long long> a;
vector<Node> seg;
Node combine(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max({l.ans, r.ans, l.suff + r.pref});
    return res;
}
Node make_node(long long v) {
    Node node;
    node.sum = v;
    node.pref = max(v, 0LL);
    node.suff = max(v, 0LL);
    node.ans = max(v, 0LL);
    return node;
}
void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = make_node(a[l - 1]);
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2, l, mid);
    build(idx * 2 + 1, mid + 1, r);
    seg[idx] = combine(seg[idx * 2], seg[idx * 2 + 1]);
}
Node query(int idx, int l, int r, int ql, int qr) {
    if(ql > r || qr < l) {
        Node ret;
        ret.sum = ret.pref = ret.suff = ret.ans = 0;
        return ret;
    }
    if(ql <= l && r <= qr)
        return seg[idx];
    int mid = (l + r) / 2;
    Node left = query(idx * 2, l, mid, ql, qr);
    Node right = query(idx * 2 + 1, mid + 1, r, ql, qr);
    return combine(left, right);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    seg.resize(4 * n);
    build(1, 1, n);
    long long res = 0;
    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        res += query(1, 1, n, l, r).ans;
    }
    cout << res << endl;
    return 0;
}
