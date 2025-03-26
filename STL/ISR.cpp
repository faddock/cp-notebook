#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]); 
    }
    
    int current_sum = a[0]; 
    int max_sum = a[0];
    
    for (int i = 1; i < n; i++) {
        current_sum = max(a[i], current_sum + a[i]);
        max_sum = max(max_sum, current_sum);
    }
    
    printf("%d\n", max_sum);
    return 0;
}