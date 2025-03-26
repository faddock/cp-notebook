/*
Coin Change
Time Limit: 1 Second
Memory Limit: 256 MB
As we all know, US dollar has six types of coins: penny (1¢), nickel (5¢), dime (10¢), quarter (25¢), half
dollar (50¢), and dollar (100¢). As a billionaire, LetianPie wants to build a house full of coins with some of
his wealth! Although LetianPie has enough amount of money to construct a large house with any type of
coins, he wants his house to be made up of coins with diverse types. As his chief software engineer, he asks
you to find out the number of ways to turn his money into six types of coins mentioned above. Two ways
are different if the sequence of coins are different (because they will yield different patterns in the house!).
For example, (1¢+ 5¢)is different from (5¢+ 1¢). Since the number can be large, print the value modulo 998
244 353.
Input
The only line of input contains a single integer n (1 ≤ n ≤ 1018) - the amount of money (in dollars) LetianPie
wants to turn to coins.
Output
Output a single integer denoting the number of ways to turn the amount into coins modulo 998 244 353.

Sample Inputs
1145141919810

sample output
930878487

solve in c++ - this is a fast exponentiation question
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int D = 100;

typedef vector<vector<long long>> matrix;

matrix matMul(const matrix &A, const matrix &B) {
    matrix C(D, vector<long long>(D, 0));
    for (int i = 0; i < D; i++){
        for (int k = 0; k < D; k++){
            if(A[i][k] != 0){
                for (int j = 0; j < D; j++){
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
    }
    return C;
}

matrix matPow(matrix base, __int128 exp) {
    matrix res(D, vector<long long>(D, 0));
    for (int i = 0; i < D; i++){
        res[i][i] = 1;
    }
    while(exp > 0){
        if((exp & 1) == 1)
            res = matMul(res, base);
        base = matMul(base, base);
        exp /= 2;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;
    __int128 T = n;
    T *= 100;

    vector<long long> dp(100, 0);
    dp[0] = 1;
    for (int i = 1; i < 100; i++){
        long long ways = 0;
        if(i - 1 >= 0)  ways = (ways + dp[i-1]) % MOD;
        if(i - 5 >= 0)  ways = (ways + dp[i-5]) % MOD;
        if(i - 10 >= 0) ways = (ways + dp[i-10]) % MOD;
        if(i - 25 >= 0) ways = (ways + dp[i-25]) % MOD;
        if(i - 50 >= 0) ways = (ways + dp[i-50]) % MOD;
        dp[i] = ways % MOD;
    }

    matrix M(D, vector<long long>(D, 0));
    M[0][0] = 1;
    M[0][4] = 1;
    M[0][9] = 1;
    M[0][24] = 1;
    M[0][49] = 1;
    M[0][99] = 1;
    for (int i = 1; i < D; i++){
        M[i][i-1] = 1;
    }

    vector<long long> state(D, 0);
    for (int i = 0; i < D; i++){
        state[i] = dp[99 - i];
    }

    __int128 exp = T - 99;
    matrix Mexp = matPow(M, exp);

    vector<long long> resVec(D, 0);
    for (int i = 0; i < D; i++){
        __int128 sum = 0;
        for (int j = 0; j < D; j++){
            sum = (sum + Mexp[i][j] * state[j]) % MOD;
        }
        resVec[i] = (long long) sum;
    }

    long long answer = resVec[0] % MOD;
    cout << answer % MOD << "\n";
    return 0;
}
