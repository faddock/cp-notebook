#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
 
    while (t--) {
        int T_a, T_s; cin >> T_a >> T_s;
        
        int total_add = 0, total_subtract = 0;
        for (int i = 0; i < T_a; ++i) {
            int a; cin >> a;
            total_add += a;
        }
        for (int i = 0; i < T_s; ++i) {
            int b; cin >> b;
            total_subtract += b;
        }
        cout << total_add - total_subtract << endl;
    }
 
    return 0;
}