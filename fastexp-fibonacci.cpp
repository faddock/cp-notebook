/*
A. Fibonacci
time limit per test0.25 seconds
memory limit per test256 megabytes
Find the 𝑛-th Fibonacci number modulo 109+7.

So, you need to find 𝐹𝑛 in the sequence defined as 𝐹0=0, 𝐹1=1 and 𝐹𝑖=𝐹𝑖−1+𝐹𝑖−2 for 𝑖≥2.

Input
An integer 𝑛 (0≤𝑛≤1018).

Output
Print the answer modulo 1000000007.

sample input 
50

sample output
586268941

Note
The first few terms of Fibonacci sequence are (0,1,1,2,3,5,8,13,…). In particular, we have 𝐹0=0, 𝐹3=2 and 𝐹6=8. And for the last sample test:

𝐹50=12586269025≡586268941(mod109+7)

solve in c++, this is a fast exponentiation question */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

struct Matrix {
    long long mat[2][2];

    Matrix operator*(const Matrix &other) const {
        Matrix result = {};
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result.mat[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return result;
    }
};

Matrix matrix_exponentiation(Matrix base, long long exp) {
    Matrix result = {1, 0, 0, 1}; // Identity matrix
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exp /= 2;
    }
    return result;
}

long long fibonacci(long long n) {
    if (n == 0) return 0;
    Matrix F = {1, 1, 1, 0};
    Matrix result = matrix_exponentiation(F, n - 1);
    return result.mat[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    cin >> n;
    cout << fibonacci(n) << endl;
    return 0;
}
