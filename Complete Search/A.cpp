#include <bits/stdc++.h>
using namespace std;

bool is_possible(vector<int>& a, int n) {
    unordered_set<int> values(a.begin(), a.end());
    queue<int> q;
    unordered_set<int> visited;
    
    q.push(0);
    visited.insert(0);
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (int num : values) {
            int next = curr + num;
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    
    for (int num : values) {
        if (!visited.count(num)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        if (is_possible(a, n)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
