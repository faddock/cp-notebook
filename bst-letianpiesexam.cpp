#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    
    int l1, l2;
    
    cin >> l1 >> l2;
    
    vector<int> x(l1), y(l2);
    for (int i = 0; i < l1; ++i) cin >> x[i];
    for (int i = 0; i < l2; ++i) cin >> y[i];
    
    sort(x.begin(), x.end(), greater<int>());
    sort(y.begin(), y.end(), greater<int>());
    
    priority_queue<pair<int, pair<int, int>>> heap;
    set<pair<int, int>> visited;
    heap.push({x[0] + y[0], {0, 0}});
    visited.insert({0, 0});
    
    long long result = 0;
    
    for (int i = 0; i < k; ++i) {
        auto top = heap.top();
        heap.pop();
        int sum = top.first;
        int xi = top.second.first;
        int yi = top.second.second;
        result += sum;
        if (xi + 1 < l1 && visited.find({xi + 1, yi}) == visited.end()) {
            heap.push({x[xi + 1] + y[yi], {xi + 1, yi}});
            visited.insert({xi + 1, yi});
        }
        if (yi + 1 < l2 && visited.find({xi, yi + 1}) == visited.end()) {
            heap.push({x[xi] + y[yi + 1], {xi, yi + 1}});
            visited.insert({xi, yi + 1});
        }
    }
    
    cout << result << endl;
    
    return 0;
}