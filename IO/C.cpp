#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Ta, Tb;
    while (scanf("%d %d", &Ta, &Tb) != EOF) {
        int a_sum = 0, b_sum = 0;
        for (int i = 0; i < Ta; i++) {
            int a; scanf("%d", &a);
            a_sum += a;
        }
        for (int i = 0; i < Tb; i++) {
            int b; scanf("%d", &b);
            b_sum += b;
        }
        printf("%d\n", a_sum-b_sum);
    }
    return 0;
}