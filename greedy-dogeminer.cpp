#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    
    vector<long long> cost(n), multiplier(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> multiplier[i];
    }
    
    double total_time = 0.0;
    double current_coins = 0.0;
    double current_rate = 1.0; // Coins per second
    
    vector<bool> bought(n, false);
    vector<int> upgrade_order; // Track which upgrades were bought
    
    while (current_coins < k) {
        // Calculate time to reach k coins with current rate
        double time_without_upgrade = (k - current_coins) / current_rate;
        double best_time = time_without_upgrade;
        int best_upgrade = -1;
        
        for (int i = 0; i < n; i++) {
            if (!bought[i]) {
                // Time to collect coins for this upgrade
                double time_to_collect = max(0.0, (cost[i] - current_coins) / current_rate);
                
                // New rate after buying this upgrade
                double new_rate = current_rate * multiplier[i];
                
                // New coins after collecting and buying the upgrade
                double new_coins = current_coins + time_to_collect * current_rate - cost[i];
                
                // Time to collect remaining coins with new rate
                double time_remaining = (k - new_coins) / new_rate;
                
                // Total additional time with this upgrade
                double total_additional_time = time_to_collect + time_remaining;
                
                if (total_additional_time < best_time) {
                    best_time = total_additional_time;
                    best_upgrade = i;
                }
            }
        }
        
        if (best_upgrade == -1) {
            // No more beneficial upgrades
            total_time += time_without_upgrade;
            current_coins = k; // We've reached the goal
        } else {
            // Buy the best upgrade
            double time_to_collect = max(0.0, (cost[best_upgrade] - current_coins) / current_rate);
            total_time += time_to_collect;
            current_coins += time_to_collect * current_rate - cost[best_upgrade];
            current_rate *= multiplier[best_upgrade];
            bought[best_upgrade] = true;
            upgrade_order.push_back(best_upgrade + 1); // +1 because upgrades are 1-indexed
        }
    }
    
    // Print the minimum time with required precision
    cout << fixed << setprecision(6) << total_time << endl;
    

    
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

solve in c++ for competitive programming

*/