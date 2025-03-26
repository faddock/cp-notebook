/*
Interstellar
Time Limit: 1 Second
Memory Limit: 256 MB
It is year 2079 and human has already built up habitats on planets across the galaxy! More excitingly,
scientists have recently invented spaceships that can travel at speed of light, which means that people can
now travel between planets almost instantly! As a travel enthusiast, LetianPie is planning his trip to explore
fascinating planets across the galaxy. He found that the Interstellar Connection Provider Company (ICPC)
has opened m interstellar routes operated by the new spaceship, and the ticket price is so cheap that everyone
can afford any number of trips! The only problem is that spaceships could crash if interplanetary dust clouds
appear, and the company has to pause operating the routes that are at risk (i.e. routes traveling across the
dust clouds) before the dust clouds disappear. However, to maintain the connection between planets, ICPC
will temporarily open new routes to replace these affected routes. Specifically, if planets x and y were
reachable from each other through the routes before a dust cloud appears but are no longer connected
afterwards, ICPC will open a new direct route between x and y if there isn’t any dust clouds between x and
y.
LetianPie wants you to help him find out if his trip will be affected by these incidents. In specific, he estimate
that he will be on planet x at time t, and he has already found that his trip might get influenced by two
nearest dust clouds located between planets l− 1 and l, and between planets r and r +1 (l ≤ x ≤ r and there
isn’t any dust clouds between planets l and r at time t). He wants you to calculate the number of planets he
can travel to from planet x (excluding x itself) given the information. But since LetianPie hasn’t finalized
his travel plan, he doesn’t know the value of x yet, so he asks you to find the answer for each planet in [l, r]
instead.
Input
The first line contains three integers n, m, and q (0 ≤ m < n ≤ 5 × 104, 1 ≤ q ≤ 5 × 104) - number of
planets, number of routes provided by ICPC, and number of queries.
The next m lines describe the routes. Each line contains two integers u and v (1 ≤ u, v ≤ n), denoting a
bidirectional route between planets u and v. It is guaranteed that there are no self-loops but there might be
multiple edges.
The last q lines describe the queries. Each line contains two integer l and r (1 ≤ l ≤ r ≤ n), as described in
the problem statement.
Output
For each query, output a single integer denotingr
x=l number of reachable planets from x.

sample input
5 2 2
1 3
2 4
1 2
2 4

sample output
0 
2

solve in c++ using square root decomposition 

*/

#include <bits/stdc++.h>
using namespace std;
 
struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n+1) { for (int i = 0; i <= n; i++) parent[i] = i; }
    int find(int a) { return parent[a] = (parent[a] == a ? a : find(parent[a])); }
    void unionn(int a, int b) { a = find(a); b = find(b); if(a != b) parent[b] = a; }
};
 
struct Query {
    int L, R, idx;
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m, q;
    cin >> n >> m >> q;
 
    DSU dsu(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        dsu.unionn(u, v);
    }
 
    vector<int> comp(n+1);
    for (int i = 1; i <= n; i++){
        comp[i] = dsu.find(i);
    }
 
    vector<int> compCopy(comp.begin()+1, comp.end());
    sort(compCopy.begin(), compCopy.end());
    compCopy.erase(unique(compCopy.begin(), compCopy.end()), compCopy.end());
    unordered_map<int,int> mp;
    for (int i = 0; i < (int)compCopy.size(); i++){
        mp[compCopy[i]] = i;
    }
    for (int i = 1; i <= n; i++){
        comp[i] = mp[ comp[i] ];
    }
    int compCount = mp.size();
 
    vector<Query> queries(q);
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        queries[i] = {l, r, i};
    }
 
    int blockSize = sqrt(n);
    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b){
        if(a.L/blockSize != b.L/blockSize) return a.L/blockSize < b.L/blockSize;
        return a.R < b.R;
    });
 
    vector<long long> ans(q, 0);
    vector<int> freq(compCount, 0);
    long long currentAnswer = 0;
 
    auto add = [&](int idx){
        int id = comp[idx];
        currentAnswer += 2LL * freq[id];
        freq[id]++;
    };
    auto remove = [&](int idx){
        int id = comp[idx];
        freq[id]--;
        currentAnswer -= 2LL * freq[id];
    };
 
    int curL = 1, curR = 0;
    for (auto &query : queries){
        int L = query.L, R = query.R;
        while(curR < R) { curR++; add(curR); }
        while(curR > R) { remove(curR); curR--; }
        while(curL < L) { remove(curL); curL++; }
        while(curL > L) { curL--; add(curL); }
        ans[query.idx] = currentAnswer;
    }
 
    for (auto &x : ans)
        cout << x << "\n";
 
    return 0;
}
