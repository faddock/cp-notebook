#include <iostream>
#define ll long long
#define MAXN 100005
using namespace std;

ll N, K, A[MAXN], Pl[MAXN], Pr[MAXN], Ql[MAXN], Qr[MAXN], DP[MAXN][MAXN];
int main() {
    cin >> N >> K;

    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= K; ++i) cin >> Pl[i];
    for (int i = 1; i <= K; ++i) cin >> Pr[i];

    for (int i = 1; i <= K; ++i) {
        // Find the index of Pl[i] in array A
        for (int j = 1; j <= N; ++j) {
            if (A[j] == Pl[i]) {
                Ql[i] = j;
                break;
            }
        }
    }
    
    for (int i = 1; i <= K; ++i) {
        // Find the index of Pr[i] in array A
        for (int j = 1; j <= N; ++j) {
            if (A[j] == Pr[i]) {
                Qr[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (Ql[i-1] == Qr[j-1]) {
                DP[i][j] = DP[i-1][j-1] + 1;
            } else {
                DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
            }
        }
    }

    cout << DP[N][N] << endl;







    /*
    we're given array of n elements - A
    two permutations - pl pr of 1 to k.
    w = len(k) - set of distinct ints
    Ql = len(k) i - index of first occurence of pli in A
    Qr = len(k) i - index of first occurance of pri in A
    QwQ sequence of A is common subsequence of Ql and Qr
    given A, and two permutations of pl and pr - find longest subsequence 

    3 2 2 1 4
    2 1 4 3
    4 3 1 2

    Ql = 2 4 5 1
    Qr = 5 1 4 3

    L QWQ - 4 0 

    so maybe we calculate Ql and Qr

    

    target = 
    */
    return 0;
}
