#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    // Basic validation: each p[i] must be at most n
    for (int i = 0; i < n; i++) {
        if (p[i] > n) {
            cout << "NO\n";
            return;
        }
    }
    
    // Step 1: Allocate large enough integers to avoid zero-sum pairs
    vector<int> a(n);
    set<int> used_values;
    
    // Step 2: For each p[i] = n, a[i] must be positive (create positive sums with all elements)
    // For each p[i] = 0, a[i] must be large negative (create negative sums with all elements)
    for (int i = 0; i < n; i++) {
        if (p[i] == n) {
            // Must be positive - use a large enough positive value
            a[i] = n + i + 1;
            used_values.insert(a[i]);
        } else if (p[i] == 0) {
            // Must be negative and large enough
            a[i] = -(3 * n);
            used_values.insert(a[i]);
        } else {
            a[i] = 0;  // Mark as unassigned
        }
    }
    
    // Step 3: Assign values for the remaining indices based on target counts
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) continue;  // Already assigned
        
        // Try values to achieve the required count of positive sums
        for (int val = -3*n; val <= 3*n; val++) {
            if (val == 0 || used_values.count(val)) continue;
            
            // Count how many positive sums this value would create with assigned elements
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] == 0) continue;  // Skip unassigned
                if (val + a[j] > 0) count++;
            }
            
            // Add self-sum if positive
            if (val > 0) count++;
            
            // Check if this value could lead to the desired count
            int remaining = n - count_if(a.begin(), a.end(), [](int x) { return x != 0; });
            if (count <= p[i] && count + remaining >= p[i]) {
                a[i] = val;
                used_values.insert(val);
                break;
            }
        }
        
        // If no value was found, no solution exists
        if (a[i] == 0) {
            cout << "NO\n";
            return;
        }
    }
    
    // Step 4: Verify the solution
    vector<int> counts(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] + a[j] > 0) counts[i]++;
        }
    }
    
    bool valid = true;
    for (int i = 0; i < n; i++) {
        if (counts[i] != p[i]) {
            valid = false;
            break;
        }
    }
    
    // Also check for zero-sum pairs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] + a[j] == 0) {
                valid = false;
                break;
            }
        }
        if (!valid) break;
    }
    
    if (valid) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << (i < n-1 ? " " : "\n");
        }
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}

/*
Inversions
Time Limit: 1 Second
Memory Limit: 2048 MB
Professor Mattox has a sequence of non-negative integers p0, p1, . . . , pn−1, and he would like to find a sequence
a0, a1, . . . , an−1 of n distinct integers such that:
1. No two (not necessarily distinct) elements ai and aj sum to 0.
2. pi is equal to the number of indices j such that ai + aj > 0 for each 0 ≤ j < n.
If multiple such sequences exist, Mattox wants one such that the maximum of the absolute values of the
elements a0, a1, . . . , an−1 is as small as possible.
Input
The input consists of multiple test cases. The first line contains an integer T which represents the number
of test cases.
For each testcase, the first line contains an integer n, the length of Mattox’s sequence. And it is guaranteed
that 1 ≤ n ≤ 2 × 105. The the next line contains a list of non-negative integers p representing Mattox’s
sequence.
For each file input, it is guaranteed that the sum of all n’s is upper bounded by 2 × 105
.
Output
For each test case, output the sequence a satisfying the given restrictions. If no such sequence exists, return
‘NO‘.
Sample Inputs
2
3
3 2 3
4
4 3 3 3

sample outputs
2 -1 3
NO

solve in c++ for competitive programming
*/