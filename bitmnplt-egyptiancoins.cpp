#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    int min_k = __builtin_popcount(n);
    if (k > n || k < min_k) {
        cout << "NO" << endl;
        return 0;
    } 

    std::vector<int> cnt(32, 0);
    int curr_cnt = min_k;
    for (int i = 0; i < 32; i++) {
        if(n & (1 << i)) {
            cnt[i]++;
        }
    }

    for (int i = 31; i > 0 && curr_cnt < k; i--) {
        while (cnt[i] > 0 && curr_cnt < k) {
            cnt[i]--;
            cnt[i-1] += 2;
            curr_cnt++;
        }
    }

    if (curr_cnt != k) {
        cout << "NO" << endl;
        return 0;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < 32; i++) {
            while(cnt[i]--) {
                cout << (1 << i) << " ";
            }
        }
    }
    cout << endl;
    return 0;



}