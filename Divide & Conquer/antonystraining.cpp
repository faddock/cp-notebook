#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
private:
    int n;
    vector<int> tree;

public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s;
    cin >> n >> s;

    vector<long long> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + t[i - 1];
    }

    vector<long long> all_values;
    for (long long val : pre) {
        all_values.push_back(val);
    }
    for (int r = 1; r <= n; ++r) {
        all_values.push_back(pre[r] - s);
    }

    sort(all_values.begin(), all_values.end());
    all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());

    int m = all_values.size();
    FenwickTree fen(m);

    long long val = pre[0];
    int idx = lower_bound(all_values.begin(), all_values.end(), val) - all_values.begin();
    int rank = idx + 1;
    fen.update(rank, 1);
    int sum_total = 1;

    long long ans = 0;

    for (int r = 1; r <= n; ++r) {
        long long current_pre = pre[r];
        long long target = current_pre - s;

        int pos = upper_bound(all_values.begin(), all_values.end(), target) - all_values.begin();
        int sum_le = fen.query(pos);
        int count = sum_total - sum_le;
        ans += count;

        int idx_insert = lower_bound(all_values.begin(), all_values.end(), current_pre) - all_values.begin();
        int rank_insert = idx_insert + 1;
        fen.update(rank_insert, 1);
        sum_total += 1;
    }

    cout << ans << endl;

    return 0;
}