/*
No More BSTs!
Time Limit: 1 Second
Memory Limit: 256 MB
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
The first line of input contains two integers n and m (1 ≤ n, m ≤ 1000) - the number of vertices in the BST
and the number of operations.
The second line contains n integers a1, . . . , an (1 ≤ ai ≤ 105), where ai is the value of vertex i. It is
guaranteed that ai are distinct.
The third line contains n− 1 integers f2, . . . , fn (1 ≤ fi ≤ n), where vertex fi is the father of vertex i. It is
guaranteed that the provided tree is a BST.
The next m lines describe LetianPie’s operations. Each line begins with one of + and−, followed by two
integers v and k (1 ≤ v ≤ n, 1 ≤ k ≤ 105), as described in the problem statement.
Output
For each operation, output YES if the tree is still a BST after the operation, and NO otherwise.

sample inputs
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