#include <bits/stdc++.h>
using namespace std;

/*
 Restock Diamonds
 ----------------
 We want to maximize the number of black diamonds Hank can purchase.
 He can buy at most 3 diamonds each time he visits a store, but can revisit
 any store if there's a cycle to exploit. The approach:

 1) Find Strongly Connected Components (SCCs).
    - If an SCC has more than 1 node, Hank can cycle through them arbitrarily many times
      and buy out all diamonds there (sum of that SCC’s diamonds).
    - If an SCC has exactly 1 node (say store i) and it has no self-loop,
      Hank can only visit it once → can take min(3, diamonds[i]) from it.

 2) Contract SCCs into a DAG (each SCC is one super-node).

 3) Find the longest path in that DAG, summing up SCC "values".
    - This is done via a topological ordering (Kahn’s).
    - The result is the maximum diamonds Hank can collect.
*/

// structs are cool
struct TarjanSCC {
    vector<int> sccIndex, sccLowLink, sccId;
    vector<bool> isOnStack;
    stack<int> sccStack;
    int currentIndex;
    int sccCount;

    TarjanSCC(int n) {
        sccIndex.assign(n, -1);
        sccLowLink.assign(n, 0);
        sccId.assign(n, -1);
        isOnStack.assign(n, false);
        while (!sccStack.empty()) sccStack.pop();
        currentIndex = 0;
        sccCount = 0;
    }

    void runTarjan(int u, const vector<vector<int>> &graph) {
        sccIndex[u] = currentIndex;
        sccLowLink[u] = currentIndex;
        currentIndex++;
        sccStack.push(u);
        isOnStack[u] = true;

        // Explore neighbors
        for (int v : graph[u]) {
            if (sccIndex[v] == -1) {
                runTarjan(v, graph);
                sccLowLink[u] = min(sccLowLink[u], sccLowLink[v]);
            }
            else if (isOnStack[v]) {
                sccLowLink[u] = min(sccLowLink[u], sccIndex[v]);
            }
        }

        // If u is a root node, pop the stack to get one SCC
        if (sccLowLink[u] == sccIndex[u]) {
            while (true) {
                int w = sccStack.top();
                sccStack.pop();
                isOnStack[w] = false;
                sccId[w] = sccCount;
                if (w == u) break;
            }
            sccCount++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<int> storeDiamonds(n);
        for (int i = 0; i < n; i++) {
            cin >> storeDiamonds[i];
        }

        vector<vector<int>> graph(n);
        graph.reserve(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
        }

        // Step 1: Run Tarjan's SCC
        TarjanSCC tarjan(n);
        for (int i = 0; i < n; i++) {
            if (tarjan.sccIndex[i] == -1) {
                tarjan.runTarjan(i, graph);
            }
        }
        vector<long long> sccValue(tarjan.sccCount, 0);

        vector<int> sccSize(tarjan.sccCount, 0);
        for (int i = 0; i < n; i++) {
            sccSize[tarjan.sccId[i]]++;
        }

        for (int i = 0; i < n; i++) {
            sccValue[tarjan.sccId[i]] += storeDiamonds[i];
        }

        // For any SCC of size == 1, we only take min(3, storeDiamonds)
        for (int i = 0; i < n; i++) {
            int comp = tarjan.sccId[i];
            if (sccSize[comp] == 1) {
                sccValue[comp] = min(3LL, (long long)storeDiamonds[i]);
            }
        }

        // Step 3: Build DAG of SCCs
        vector<vector<int>> condensedGraph(tarjan.sccCount);
        vector<int> inDegree(tarjan.sccCount, 0);
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                int sccU = tarjan.sccId[u];
                int sccV = tarjan.sccId[v];
                if (sccU != sccV) {
                    condensedGraph[sccU].push_back(sccV);
                }
            }
        }

        // Compute inDegree of each SCC
        for (int u = 0; u < (int)condensedGraph.size(); u++) {
            for (int v : condensedGraph[u]) {
                inDegree[v]++;
            }
        }

        // Topological DP (Kahn’s Algorithm)
        // dp[i] = maximum diamonds collectible upon reaching SCC i
        vector<long long> maxDiamondsUpTo(tarjan.sccCount, 0);

        queue<int> zeroInDegree;
        for (int i = 0; i < tarjan.sccCount; i++) {
            if (inDegree[i] == 0) {
                maxDiamondsUpTo[i] = sccValue[i];
                zeroInDegree.push(i);
            }
        }

        long long result = 0; // we love long long 
        while (!zeroInDegree.empty()) {
            int u = zeroInDegree.front();
            zeroInDegree.pop();
            result = max(result, maxDiamondsUpTo[u]);
            for (int v : condensedGraph[u]) {
                long long candidate = maxDiamondsUpTo[u] + sccValue[v];
                if (candidate > maxDiamondsUpTo[v]) {
                    maxDiamondsUpTo[v] = candidate;
                }
                if (--inDegree[v] == 0) {
                    zeroInDegree.push(v);
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}


/*

Restock Diamonds
Time Limit: 2 Second
Memory Limit: 2048 MB
Hank, a jewelry reseller, wants to restock his black diamond inventory. In this city, there are n stores and
m directed routes between them. Each store has a limited number of black diamonds, and every time Hank
visits a store, he can purchase at most 3 diamonds due to security restrictions. Security guards in stores
with make sure he did not purchase more than 3 diamonds, but he can revisit any store in his trip and
purchase more.
Hank wants to maximize the number of black diamonds he can purchase by traversing the stores through
their directed routes. Help Hank determine the maximum number of black diamonds he can purchase when
his trip could start from any store and stop at any store.
Input
The first line contains an integer T , the number of test cases.
For each test case:
• The first line contains two integers: n (the number of stores) and m (the number of directed routes
between stores).
• The second line contains n integers, representing the number of black diamonds available at each store.
• The next m lines each contain two integers: x y, representing a directed route from store x to store
y.
The constraints are:
• 1 ≤ T ≤ 3: The number of test cases T is between 1 and 3.
• 2 ≤ n ≤ 105: The number of stores n is between 2 and 105
.
• 0 ≤ m ≤ n2: The number of directed routes m is between 0 and min(n2
, 2 × 105)
• The number of black diamonds at each store is between 0 and 100. Some stores do not have black
diamonds.
• Stores are numbered from 0 to n− 1.
There could be multiple edges between stores, but there will be no self-edges.
Output
For each test case, output a single integer: the maximum number of black diamonds Hank can purchase
while adhering to the constraints.
Sample Inputs
2
5 5
1 1 3 7 9
0 2
2 3
0 4
1 0
4 1
5 4
1 1 3 7 9
2 3
0 4
1 0
4 1
Sample Outputs
17
11
*/