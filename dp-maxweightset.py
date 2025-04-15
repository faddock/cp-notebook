# dp[i] gives the max weighter independent set for the first i nodes in tree
# target: dp[n]
# dp[i] = 
from collections import defaultdict
n = int(input())
adjList = defaultdict(list)
for i in range(n-1):
    v1, v2 = map(int, input().split())
    adjList[v2].append(v1)
    adjList[v1].append(v2)

weights = list(map(int, input().split()))

active = [False for _ in range(n)]
active[0] = True

dp = [0 for _ in range(n+1)]
dp[1] = weights[0]

print (weights)
print (adjList)
# for i in range(n):
#     for j in range(1,i):
        # for ith adding node, if there is a connection with an active node in the past
        # it cannot be a connection


        # 0 - 1 - 2     3-6-2    3(1-3) 2
        # if adjList[]
        

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Frame {
    int node, parent, childIndex;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> weight(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> weight[i];
    }
    
    vector<long long> dp0(n + 1, 0), dp1(n + 1, 0);
    
    vector<Frame> stack;
    stack.reserve(n);
    stack.push_back({1, 0, 0});
    
    while (!stack.empty()){
        Frame &top = stack.back();
        int node = top.node;
        int parent = top.parent;
        if (top.childIndex < (int)adj[node].size()){
            int child = adj[node][top.childIndex];
            top.childIndex++;
            if (child == parent) continue;
            stack.push_back({child, node, 0});
        } else {
            for (int child : adj[node]){
                if (child == parent) continue;
                dp0[node] += max(dp0[child], dp1[child]);
                dp1[node] += dp0[child];
            }
            dp1[node] += weight[node];
            stack.pop_back();
        }
    }
    
    cout << max(dp0[1], dp1[1]) << '\n';
    return 0;
}
