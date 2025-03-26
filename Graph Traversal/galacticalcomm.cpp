#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
    int n; cin >> n;

    vector<vi> cost(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> cost[i][j];
        }
    }
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;

        vector<vi> newcost = cost;
        long long sum = 0;
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                newcost[x][y] = min({cost[x][y], cost[x][a] + c + cost[b][y], cost[x][b] + c + cost[a][y]});
                sum += newcost[x][y];
            }
        }
        cost = newcost;
        cout << sum/2 << " ";   
    }
    cout << "\n";
    return 0;
}