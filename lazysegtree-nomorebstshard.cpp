/*
No More BSTs! (Hard Version)
Time Limit: 1 Second
Memory Limit: 2048 MB
If you have seen the normal version of this problem in this class before, the only difference
between the two versions is the constraints on n and m.
You just created a binary search tree from an array of size n using the knowledge you learned from CS 495.
However, LetianPie doesn’t like BSTs so he wants to destroy your BST. In specific, you know that he will
choose m vertices v1, . . . , vm (the vertices are not necessarily distinct), and for each vertex vi, he will perform
one of the following operations:
• + vi k: add k to all vertices in the subtree rooted at vi.
•− vi k: subtract k from all vertices in the subtree rooted at vi.
You don’t want LetianPie to destroy your BST, so you want to know if he will reach his goal after the
operations. For each operation, check if the new tree is still a valid BST after LetianPie has performed the
operation (as well as all operations beforehand).
A tree is a valid BST if for all vertices v, all vertices in its left subtree have values less than or equal to
the value of v, and all vertices in its right subtree have values greater than or equal to the value of v. For
simplicity, the tree is rooted at vertex 1.
Input
The first line of input contains two integers n and m (1 ≤ n, m ≤ 105) - the number of vertices in the BST
and the number of operations.
The second line contains n integers a1, . . . , an (1 ≤ ai ≤ 105), where ai is the value of vertex i. It is
guaranteed that ai are distinct.
The third line contains n− 1 integers f2, . . . , fn (1 ≤ fi ≤ n), where vertex fi is the father of vertex i. It is
guaranteed that the provided tree is a BST.
The next m lines describe LetianPie’s operations. Each line begins with one of + and−, followed by two
integers v and k (1 ≤ v ≤ n, 1 ≤ k ≤ 105), as described in the problem statement.
Output
For each operation, output YES if the tree is still a BST after the operation, and NO otherwise.

sample input
5 3
3 1 5 2 4
1 1 2 3
- 3 1
- 5 2
+ 3 10

sample output
YES
NO
YES

solve in c++
*/

#include <bits/stdc++.h>
using namespace std;
 
struct SegTree {
    int n;
    vector<int> tree;
    SegTree(int n) : n(n) {
        tree.assign(4*n, 0);
    }
    void build(vector<int> &arr, int idx, int l, int r) {
        if(l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, idx*2, l, mid);
        build(arr, idx*2+1, mid+1, r);
        tree[idx] = min(tree[idx*2], tree[idx*2+1]);
    }
    void update(int idx, int l, int r, int pos, int delta) {
        if(l == r) {
            tree[idx] += delta;
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) update(idx*2, l, mid, pos, delta);
        else update(idx*2+1, mid+1, r, pos, delta);
        tree[idx] = min(tree[idx*2], tree[idx*2+1]);
    }
    int query(){
        return tree[1];
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
    vector<int> val(n+1);
    for (int i = 1; i <= n; i++){
        cin >> val[i];
    }

    vector<int> leftChild(n+1, 0), rightChild(n+1, 0);
    for (int i = 2; i <= n; i++){
        int p;
        cin >> p;
        if(val[i] < val[p]){
            leftChild[p] = i;
        } else {
            rightChild[p] = i;
        }
    }
 
    if(n == 1){
        for (int i = 0; i < m; i++){
            char op; int v, k;
            cin >> op >> v >> k;
            cout << "YES\n";
        }
        return 0;
    }
 
    vector<int> inIndex(n+1, 0); 
    vector<int> orderArr(n+1, 0); 
    int pos = 1;
    int cur = 1;
    stack<int> s;
    while(cur != 0 || !s.empty()){
        while(cur != 0){
            s.push(cur);
            cur = leftChild[cur];
        }
        cur = s.top(); s.pop();
        inIndex[cur] = pos;
        orderArr[pos] = cur;
        pos++;
        cur = rightChild[cur];
    }
 

    vector<int> subSize(n+1, 0);
    vector<int> orderPost;
    orderPost.reserve(n);
    {
        stack<int> st;
        st.push(1);
        while(!st.empty()){
            int v = st.top(); st.pop();
            orderPost.push_back(v);
            if(leftChild[v] != 0) st.push(leftChild[v]);
            if(rightChild[v] != 0) st.push(rightChild[v]);
        }
        reverse(orderPost.begin(), orderPost.end());
        for (int v : orderPost){
            int leftSz = (leftChild[v] ? subSize[leftChild[v]] : 0);
            int rightSz = (rightChild[v] ? subSize[rightChild[v]] : 0);
            subSize[v] = 1 + leftSz + rightSz;
        }
    }
 
    vector<int> subStart(n+1,0), subEnd(n+1,0);
    for (int v = 1; v <= n; v++){
        int leftSz = (leftChild[v] ? subSize[leftChild[v]] : 0);
        subStart[v] = inIndex[v] - leftSz;
        int rightSz = (rightChild[v] ? subSize[rightChild[v]] : 0);
        subEnd[v] = inIndex[v] + rightSz;
    }
 
    vector<int> B(n+1, 0);
    for (int i = 1; i <= n; i++){
        int v = orderArr[i];
        B[i] = val[v];
    }

    vector<int> diff(n, 0);
    for (int i = 1; i < n; i++){
        diff[i] = B[i+1] - B[i];
    }

    SegTree seg(n);
    seg.build(diff, 1, 1, n-1);
 
    for (int i = 0; i < m; i++){
        char op;
        int v, k;
        cin >> op >> v >> k;
        int L = subStart[v], R = subEnd[v];
        if(L > 1){
            int delta = (op == '+' ? k : -k);
            seg.update(1, 1, n-1, L-1, delta);
        }
        if(R < n){
            int delta = (op == '+' ? -k : k);
            seg.update(1, 1, n-1, R, delta);
        }
        cout << (seg.query() >= 0 ? "YES" : "NO") << "\n";
    }
    return 0;
}
