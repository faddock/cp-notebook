#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using my_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

long long unique_id = 0;
const long long INF_NEG = -1LL << 60;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    my_set<pair<long long, long long>> bst;

    while (n--) {
        string operation;
        cin >> operation;
        
        if (operation == "Insert") {
            long long value;
            cin >> value;
            bst.insert({value, unique_id++});
        } 
        else if (operation == "Delete") {
            long long value;
            cin >> value;
            auto it = bst.lower_bound({value, INF_NEG});
            if (it != bst.end() && it->first == value) {
                bst.erase(it);
            }
        } 
        else if (operation == "Rank") {
            long long value;
            cin >> value;
            long long rank = bst.order_of_key({value, INF_NEG});
            cout << rank << "\n";
        } 
        else if (operation == "Kth") {
            long long k;
            cin >> k;
            if (k < 1 || k > bst.size()) {
                cout << "Wrong!\n";
            } else {
                auto it = bst.find_by_order(k - 1);
                cout << it->first << "\n";
            }
        }
    }

    return 0;
}
