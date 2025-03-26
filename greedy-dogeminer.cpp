#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, k;
    cin >> n >> k;
    
    vector<long long> c(n), p(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    vector<bool> used(n, false); // Track which upgrades have been used
    vector<int> upgradeSequence; // Store the sequence of upgrades (1-indexed)
    
    double rate = 1.0; // Initial production rate: 1 coin per second
    double time = 0.0; // Total time elapsed
    double coins = 0.0; // Current number of coins
    
    while (coins < k) {
        double timeToFinish = (k - coins) / rate;
        
        double bestTime = timeToFinish;
        int bestUpgrade = -1;
        
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            
            double timeToEarn = max(0.0, (c[i] - coins) / rate);
            double coinsAfter = coins + timeToEarn * rate - c[i];
            double newRate = rate * p[i];
            double timeRemaining = (k - coinsAfter) / newRate;
            double totalTime = timeToEarn + timeRemaining;
            
            if (totalTime < bestTime) {
                bestTime = totalTime;
                bestUpgrade = i;
            }
        }

        if (bestUpgrade == -1) {
            time += timeToFinish;
            coins = k;
        } else {
            double timeToEarn = max(0.0, (c[bestUpgrade] - coins) / rate);
            time += timeToEarn;
            coins += timeToEarn * rate - c[bestUpgrade];
            rate *= p[bestUpgrade];
            used[bestUpgrade] = true;
            upgradeSequence.push_back(bestUpgrade + 1);
        }
    }
    
    cout << fixed << setprecision(6) << time << endl;    
    if (!upgradeSequence.empty()) {
        for (size_t i = 0; i < upgradeSequence.size(); ++i) {
            cout << upgradeSequence[i];
            if (i < upgradeSequence.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    } else {
        cout << endl; 
    }
    return 0;
}

/*

Doge Miner
Time Limit: 1 Second
Memory Limit: 2048 MB
Doge Miner is a famous browser game where the goal is to click the Doge on your screen as many times
as you can (perhaps you’ve played similar games such as Cookie Clicker). Since you are playing on your
laptop’s trackpad, you can only click once per second. This means that every second you gain one coin.
The game also has n upgrades. Each upgrades costs ci coins to buy, and afterwards, the time it takes for
you to gain a coin is divided by pi. You can only buy each upgrade once.
You know that it takes k coins to go to the Moon. Since you are very eager to reach the Moon, you want to
know the minimum time it takes to get k coins.
Input
The first line contains integer n (0 ≤ n ≤ 105) and k (0 ≤ k ≤ 109), denoting the number of upgrades and
the total number of coins you want to gain.
The next line contains n integers c1...cn (1 ≤ ci ≤ 109), where ci denotes the cost of the i-th upgrade.
The next line contains n integers p1...pn (2 ≤ pi ≤ 109), where pi denotes the production rate multiplier of
the i-th upgrade.
Output
On the first line, output the minimum time it takes for you to get k coins. Your answer will be considered
correct if it has at most 10−6 absolute or relative error.

Sample Inputs
3 10
5 8 3
3 4 2

Sample Outputs
7.166667
3 1

Note
For the sample, you should buy upgrade 3 then upgrade 1.


solve in c++

*/