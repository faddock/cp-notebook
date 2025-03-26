#include <bits/stdc++.h>
using namespace std;
 
struct Fenw {
    int n;
    vector<int> fenw;
    Fenw(int n) : n(n), fenw(n + 1, 0) {}
    
    void update(int i, int delta) {
        for (; i <= n; i += i & -i)
            fenw[i] += delta;
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += fenw[i];
        return sum;
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, w, h, k, c;
    cin >> n >> w >> h >> k >> c;
    
    vector<vector<int>> coinsAt(w + 1);
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        coinsAt[x].push_back(y);
    }
    
    Fenw bit(h);
    
    long long ans = 0;
    for (int a = 0; a <= w; a++){
        if(a > 0) {
            for (int y : coinsAt[a]) {
                bit.update(y, 1);
            }
        }
        for (int b = 1; b <= h; b++){
            int count = bit.query(b);
            long long profit = (long long) k * count - (long long) c * a * b;
            ans = max(ans, profit);
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}


/*

Gold Coins
Time Limit: 1 Second
Memory Limit: 2048 MB
Your best friend just sent you a message saying they have discovered a site full of gold coins! They generously
offer to share the gold coins with you, but there is one remaining question - you need to purchase the land
in order to dig up the gold coins.
The site can be viewed as a rectangle with vertices (0, 0), (w, 0), (0, h), and (w, h). Using a metal detector,
your friend has obtained a map indicating the location of each gold coin, and each coin is worth k dollars.
The owner of the site allows you to select two integers a and b (0 ≤ a ≤ w, 0 ≤ b ≤ h), and purchase the
rectangle bounded by x = 0, x = a, y = 0, and y= b with c dollars per unit square. Given the location of
each gold coin, calculate the maximum profit you and your friend can receive.
Input
The first line contains four integers n, w, h, k, c (1 ≤ n ≤ 105, 1 ≤ w· h ≤ 106, 1 ≤ k, c ≤ 109) - number of
gold coins, width of the field, height of the field, value of each gold coin, and cost of buying each unit square.
The next n lines describe the locations of each gold coin. Each line contains two integers x and y (1 ≤ x ≤
w, 1 ≤ y ≤ h)- the location of one gold coin. It is possible that multiple gold coins are on the same point.
Output
Output a single integers denoting the maximum profit you can receive.

sample input
3 5 5 3 1
1 1
1 2
2 1

sample output
5

solve in c++, using fenwick tree
*/