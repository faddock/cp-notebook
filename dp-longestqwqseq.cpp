#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    
    vector<int> a(n);
    for (auto &x : a) 
        cin >> x;

    vector<int> w = a;
    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());
    int wSize = w.size();
    
    unordered_map<int, int> mapping;
    for (int i = 0; i < wSize; i++) {
        mapping[w[i]] = i;
    }
    
    vector<int> firstOccurrence(wSize, -1), lastOccurrence(wSize, -1);
    for (int i = 0; i < n; i++){
        int idx = mapping[a[i]];
        if (firstOccurrence[idx] == -1)
            firstOccurrence[idx] = i + 1;
        lastOccurrence[idx] = i + 1;
    }
    
    vector<int> pl(k), pr(k);
    for (int i = 0; i < k; i++) 
        cin >> pl[i];
    for (int i = 0; i < k; i++) 
        cin >> pr[i];

    vector<int> Ql(k), Qr(k);
    for (int i = 0; i < k; i++){
        int idx = pl[i] - 1; 
        Ql[i] = firstOccurrence[idx];
    }
    for (int i = 0; i < k; i++){
        int idx = pr[i] - 1;
        Qr[i] = lastOccurrence[idx];
    }
    
    vector<int> pos(n + 2, -1);
    for (int i = 0; i < k; i++){
        if(Qr[i] <= n)
            pos[Qr[i]] = i;
    }
    
    vector<int> seq;
    for (int i = 0; i < k; i++){
        if (Ql[i] <= n && pos[Ql[i]] != -1)
            seq.push_back(pos[Ql[i]]);
    }
    
    vector<int> lis;
    for (int x : seq) {
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end())
            lis.push_back(x);
        else
            *it = x;
    }
    
    cout << lis.size() << endl;
    return 0;
}





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

