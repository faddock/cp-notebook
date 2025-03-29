#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
struct Game {
    ll p, pdisc, diff; 
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, k;
    ll c;
    cin >> n >> k >> c;
    vector<Game> games(n);
    for (int i = 0; i < n; i++){
        cin >> games[i].p;
    }
    for (int i = 0; i < n; i++){
        cin >> games[i].pdisc;
        games[i].diff = games[i].p - games[i].pdisc;
    }
    
    sort(games.begin(), games.end(), [](const Game &a, const Game &b){
        return a.pdisc < b.pdisc;
    });
    
    vector<ll> prefP(n+1, 0), prefPd(n+1, 0);
    for (int i = 0; i < n; i++){
        prefP[i+1] = prefP[i] + games[i].p;
        prefPd[i+1] = prefPd[i] + games[i].pdisc;
    }

    auto canBuy = [&](int x) -> bool {
        if(x > n) return false;
        ll cost = 0;
        if(x <= k){
            cost = prefPd[x];
        } else {
            cost = prefP[x];  
            vector<ll> diffs;
            diffs.reserve(x);
            for (int i = 0; i < x; i++){
                diffs.push_back(games[i].diff);
            }
            sort(diffs.begin(), diffs.end(), greater<ll>());
            ll save = 0;
            for (int i = 0; i < k; i++){
                save += diffs[i];
            }
            cost -= save;
        }
        return cost <= c;
    };
 
    int lo = 0, hi = n;
    int ans = 0;
    while(lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if(canBuy(mid)){
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}


/*
Sale!
Time Limit: 1 Second
Memory Limit: 256 MB
Aggrovector loves playing video games and he spends hundreds of hours playing video games every month!
As a computer science student, Aggrovector wants to use his expertise to help him save money buying video
games on Steam. In this year’s Black Friday, Aggrovector found that many games on Steam are on sale, so
he wants to use this chance to buy many video games he wants to play.
Specifically, Aggrovector has n video games in his cart, and the original price of the i-th game is pi dollars.
During the sale, Aggrovector will receive k coupons, and applying a coupon on the i-th game will lower
the price of the game from pi to p′
i dollars. Aggrovector decides to spend at most c dollars buying the
video games, and he wants to find out the maximum number of games he can buy by applying the coupons
optimally.
Input
The first line of input contains three integers n, k and c (1 ≤ n, k ≤ 105, 1 ≤ c ≤ 109) - number of games in
the cart, number of coupons, and the budget.
The second line contains n integers p1, . . . , pn (1 ≤ pi ≤ 109) - the original price of each game.
The third line contains n integers p′
1, . . . , p′
n (1 ≤ p′
i ≤ pi) - the discounted price of each game if a coupon is
applied to the game.
Output
Output a single integer denoting the number of games Aggrovector can buy given his budget.

sample input 
5 2 5
1 2 3 4 5
1 1 1 1 1

sample output
4

solve in c++ for competitive programming */