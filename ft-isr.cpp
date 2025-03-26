#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, idx;
};

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    
    void update(int i, int delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
    
    int queryRange(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    vector<Query> queries(m);
    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        queries[i] = {l, r, i};
    }
    
    // Sort queries by r value
    sort(queries.begin(), queries.end(), [](const Query &q1, const Query &q2){
        return q1.r < q2.r;
    });
    
    vector<int> ans(m, 0);
    //store last occurrence (initialize to 0)
    vector<int> lastOccurrence(1000001, 0);
    BIT bit(n);
    
    int current_r = 0;
    // Process each query in increasing order of r
    for(auto &q : queries){
        while(current_r < q.r){
            current_r++;
            int food = a[current_r];
            // If this food has appeared before, remove its previous contribution
            if(lastOccurrence[food] != 0){
                bit.update(lastOccurrence[food], -1);
            }
            // Mark the current position as the latest occurrence
            bit.update(current_r, 1);
            lastOccurrence[food] = current_r;
        }
        ans[q.idx] = bit.queryRange(q.l, q.r);
    }
    
    for(auto num : ans)
        cout << num << "\n";
    
    return 0;
}


/*

ISR II
Time Limit: 1 Second
Memory Limit: 2048 MB
After his last visit to ISR Dining Center, LetianPie found the food was so good that he decided to go to ISR
for dinner regularly. However, LetianPie doens’t like eating the same kind of food everyday because he will
soon get bored. From Illinois App, LetianPie knows that for the following n days, ISR will provide food of
type ai on the i-th day. LetianPie has m plans for the next days, where in the i-th plan, LetianPie will have
dinner at ISR on days li, . . . , ri, and go to Green Street for dinner for other days. He wants you to help him
calculate the number of different types of food he can eat at ISR for each plan he has so that he can decide
which plan is the best for him.
Input
The first line contains two integer n and m (1 ≤ n, m ≤ 105), as described in the statement.
The next line contains n integers a1, . . . , an (1 ≤ ai ≤ 106) - the type of food served by ISR on each day.
The next m lines describe LetianPie’s plans. Each line contains two integers l and r (1 ≤ l ≤ r ≤ n) -
LetianPie will go to ISR for dinner only on days l, . . . , r.
Output
For each plan, output the number of distinct types of food LetianPie can eat at ISR.

sample inputs
5 3
1 2 3 2 1
2 4
1 3
2 5

sample outputs
2
3
3

solve in c++ 
hints: sort queries in increasing order
for each r <- 1 to N, record the last occurence for each value
*/

