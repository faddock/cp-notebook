/*Trip II
Time Limit: 1 Second
Memory Limit: 2048 MB
After your exciting but intensive trip, you are exhausted and want to go back home immediately. However,
you still might need to make multiple layovers during your trip because there aren’t any direct flights back
to your home airport. You have looked up the flights for the next a few days and want to book the flights
that can get you home (and this time you don’t need to worry about the ticket price because they are so
cheap!). Moreover, you have decided to give yourself a good rest by booking first-class tickets for all flights!
However, you still need to minimize the total time for your layovers because they are very tiring (you have
to stay awake not to miss your flight!).
Specifically, you have found that there are m flights connecting n cities. Each flight departs from city a
at time ts and arrives at city b at time te (each flight is non-recurring and one-directional). Your fatigue
increases by t if you need to stay at any airport for t minutes (including the starting airport but excluding
the final destination). You want to select the flights that minimize your total fatigue (you don’t need to
minimize the total flight time because you can get really good rest in first-class cabin!). Assume that you
are currently at airport 1 at time 0 and your home airport is n, and you can catch any flight with departure
time no less than the arrival time for the current flight (don’t do this in reality!).
Input
The first line of input contains two integers n and m (2 ≤ n ≤ 105, 1 ≤ m ≤ 105) - the number of cities and
the number of routes between cities.
The next m lines describe the flights. Each line contains four integers a, b, ts, te (1 ≤ a, b ≤ n, 1 ≤ ts < te ≤
109), denoting a flight from city a to city b that departs at time ts and arrives at time te. It is guaranteed
that you can reach airport n from airport 1 given the constraints and there are no self-loops.
Output
Output a single integer denoting the minimum fatigue you will get during the trip.

sample input
4 4
1 2 3 20
1 3 5 10
2 3 50 100
3 4 100 120

sample output
33

solve in c++ using lazy segement trees
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1LL << 60;

struct Flight {
    int a, b;
    int ts, te;
};

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree() {}
    SegTree(int n) : n(n) {
        tree.assign(4*n, INF);
    }
    void update(int idx, int l, int r, int pos, ll val) {
        if(l == r) {
            tree[idx] = min(tree[idx], val);
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) update(idx*2, l, mid, pos, val);
        else update(idx*2+1, mid+1, r, pos, val);
        tree[idx] = min(tree[idx*2], tree[idx*2+1]);
    }
    ll query(int idx, int l, int r, int ql, int qr) {
        if(ql > r || qr < l)
            return INF;
        if(ql <= l && r <= qr)
            return tree[idx];
        int mid = (l + r) / 2;
        return min(query(idx*2, l, mid, ql, qr), query(idx*2+1, mid+1, r, ql, qr));
    }
};

struct CityData {
    vector<int> keys;
    SegTree seg;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Flight> flights(m);
    for (int i = 0; i < m; i++){
        cin >> flights[i].a >> flights[i].b >> flights[i].ts >> flights[i].te;
    }

    vector<CityData> cityData(n+1);
    for (int i = 0; i < m; i++){
        int a = flights[i].a;
        cityData[a].keys.push_back(flights[i].ts);
    }
    for (int i = 1; i <= n; i++){
        if(!cityData[i].keys.empty()){
            sort(cityData[i].keys.begin(), cityData[i].keys.end());
            cityData[i].keys.erase(unique(cityData[i].keys.begin(), cityData[i].keys.end()), cityData[i].keys.end());
            cityData[i].seg = SegTree((int)cityData[i].keys.size());
        }
    }

    sort(flights.begin(), flights.end(), [](const Flight &f1, const Flight &f2){
        return f1.ts > f2.ts;
    });

    for (int i = 0; i < m; i++){
        int a = flights[i].a, b = flights[i].b;
        int ts = flights[i].ts, te = flights[i].te;

        ll queryVal;
        if(b == n) {
            queryVal = te;
        } else {
            if(cityData[b].keys.empty()){
                queryVal = INF;
            } else {
                int pos = int(lower_bound(cityData[b].keys.begin(), cityData[b].keys.end(), te) - cityData[b].keys.begin());
                if(pos == (int)cityData[b].keys.size())
                    queryVal = INF;
                else
                    queryVal = cityData[b].seg.query(1, 0, cityData[b].seg.n - 1, pos, cityData[b].seg.n - 1);
            }
        }
        ll dp = queryVal - te;

        if(!cityData[a].keys.empty()){
            int pos = int(lower_bound(cityData[a].keys.begin(), cityData[a].keys.end(), ts) - cityData[a].keys.begin());
            if(pos < (int)cityData[a].keys.size()){
                cityData[a].seg.update(1, 0, cityData[a].seg.n - 1, pos, dp + ts);
            }
        }
    }

    ll ans;
    if(cityData[1].keys.empty()){
        ans = INF;
    } else {
        int pos = int(lower_bound(cityData[1].keys.begin(), cityData[1].keys.end(), 0) - cityData[1].keys.begin());
        if(pos == (int)cityData[1].keys.size())
            ans = INF;
        else
            ans = cityData[1].seg.query(1, 0, cityData[1].seg.n - 1, pos, cityData[1].seg.n - 1);
    }
    cout << ans << "\n";
    return 0;
}
