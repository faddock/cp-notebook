/*
Bandwidth
Time Limit: 1 Second
Memory Limit: 256 MB
Bandwidth measure the amount of data that can be transferred in a certain amount of time. The bandwidth
of a path is the minimum bandwidth of all wires in the path. The University of Illinois campus can be
viewed as a network with n vertices (buildings) connected by m edges (wires). As a technical staff, you are
now asked to compute the minimum bandwidth for transferring data from any building to another in the
network so that the university knows how to upgrade the network.
Input
The first line of input contains two integers n, m (2 ≤ n ≤ 105
, n− 1 ≤ m ≤ min(105
,
buildings and number of connections.
n(n−1)
2 ) - number of
The next m lines describe the edges. Each line contains three integers u, v, and w (1 ≤ u, v ≤ n, 1 ≤ w ≤ 109),
denoting an undirected connection between building u and building v with bandwidth w. It is guaranteed
that the graph is connected, and there are no self-loops or multiple edges.
Output
Output a single integer denoting the minimum bandwidth for transferring data from any building to another
in the network.

sample input
4 6
1 2 1
1 3 2
2 3 3
1 4 5
2 4 1
3 4 1

sample output
2

solve in c++
*/
