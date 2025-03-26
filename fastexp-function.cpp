/*
Function
Time Limit: 1 Second
Memory Limit: 256 MB
A function f is defined as follows:
• f (0) = 4
• f (1) = 9
• f (2) = 5
• ∀n > 2, f (n) = 4f (n−3) + 9f (n−2) + 5f (n−1)
Given a number k (0 ≤k ≤1018), find the value of f (k). Since the value might be too large, output the
value modulo 998 244 353.
Input
The only line of input contains a single integer k (0 ≤k ≤1018), as described in the problem statement.
Output
Output the value of f (k) modulo 998 244 353.

sample input
10

sample output
634970013

solve in c++ - this is a fast exponentation question 
*/

#include <iostream>
using namespace std;
 
typedef long long ll;
const ll MOD = 998244353;
 
struct Matrix {
    ll m[3][3];
};
 
Matrix multiply(Matrix A, Matrix B) {
    Matrix C{};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            C.m[i][j] = 0;
            for (int k = 0; k < 3; k++){
                C.m[i][j] = (C.m[i][j] + A.m[i][k] * B.m[k][j]) % MOD;
            }
        }
    }
    return C;
}
 
Matrix matrixExpo(Matrix base, ll exp) {
    Matrix result{};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            result.m[i][j] = (i == j);
        }
    }
    while(exp > 0) {
        if(exp & 1)
            result = multiply(result, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    long long k;
    cin >> k;
    
    if(k == 0) {
        cout << 4 << "\n";
        return 0;
    }
    if(k == 1) {
        cout << 9 << "\n";
        return 0;
    }
    if(k == 2) {
        cout << 5 << "\n";
        return 0;
    }
 
    Matrix T;
    T.m[0][0] = 5; T.m[0][1] = 9; T.m[0][2] = 4;
    T.m[1][0] = 1; T.m[1][1] = 0; T.m[1][2] = 0;
    T.m[2][0] = 0; T.m[2][1] = 1; T.m[2][2] = 0;
 
    Matrix Texp = matrixExpo(T, k - 2);
    ll f_k = (Texp.m[0][0] * 5 + Texp.m[0][1] * 9 + Texp.m[0][2] * 4) % MOD;
    cout << f_k << "\n";
 
    return 0;
}
