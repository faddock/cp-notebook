#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    long long count = 0;
    
    for(int center = 0; center < n; center++){
        int left = center, right = center;
        while(left >= 0 && right < n && s[left] == s[right]){
            count++;
            left--;
            right++;
        }
    }
    
    for(int center = 0; center < n - 1; center++){
        int left = center, right = center + 1;
        while(left >= 0 && right < n && s[left] == s[right]){
            count++;
            left--;
            right++;
        }
    }
    
    cout << count <<endl;
    return 0;
}
