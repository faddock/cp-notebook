#include <bits/stdc++.h>
using namespace std;

int main() {

    int Ta, Ts;
    while (scanf("%d %d", &Ta, &Ts) && !(Ta == 0 && Ts == 0)) {
        int add_sum = 0, sub_sum = 0, num;
        
        for (int i = 0; i < Ta; i++) {
            scanf("%d", &num);
            add_sum += num;
        }
        
        for (int i = 0; i < Ts; i++) {
            scanf("%d", &num);
            sub_sum += num;
        }
        
        printf("%d\n", add_sum - sub_sum);
    }
    return 0;
}