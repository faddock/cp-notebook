/*

Squid Game - Find Your Room
Time Limit: 1 Second
Memory Limit: 256 MB
Mattox started a Squid Game! As a kind (trapped) student in the CS491 class, you are invited (blindfolded)
to the game!
In this round, the host is the benevolent Char, and the game is ”Find Your Room”!
The rule of the game is as follows:
1. The game contains Q turns. The students will be placed in an open space with lots of rooms.
2. At the start of each turn, Char will shout out a number mi.
3. Each student need to go in to one of the rooms numbered with 1, . . . , mi within a time limit.
4. The students will win the turn if the maximum and minimum number of students within the rooms
does not differ by more than one.
You quickly realized that you have a way to always guarantee a win for the students!
The strategy is:
1. Before the first round, each of the N student will get a number from 1 to N.
2. When a turn starts, and Char shout out the number mi, the student numbered ai will go to room
(ai− 1) mod mi + 1.
3. Then it is guaranteed that you will win.
Unfortunately, Char also knows about this strategy. So in addition to the previous requirement, he gives
each student a secret integer key. When a turn ends, he will choose a room number pi, and randomly pick
a student to compute the sum of all students’ secret key in room pi. If the student can’t give the correct
answer within the time limit, you will lose the game. Since you have a long time to prepare before the first
turn start, can you find a way to fast track the calculation if you will adopt the strategy mentioned above?
Input
number of turns.
The first line of input contains two integers N and Q (1 ≤ N, Q ≤ 105), the number of students and the
The second line contains N integers a1, . . . , an (1 ≤ ai ≤ 109), the secret key of the ith student.
The next Q lines each contains two integers mi and pi (1 ≤ mi ≤ N , 1 ≤ pi ≤ mi), the number of rooms
and the room you will race to get the sum of secret key in room pi.
Output
For each turn, output a single integer denoting the sum of secret key in room pi.

sample input
5 2
1 2 3 4 5
3 1
2 2

sample output
5
6

solve in c++ using square root decomposition
*/

#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int N, Q; cin >> N >> Q;
    
    vector<long long> a(N+1);
    for (int i = 1; i <= N; i++){
        cin >> a[i];
    }
    
    int B = sqrt(N);
    vector<vector<long long>> dp(B+1);
    for (int m = 1; m <= B; m++){
        dp[m].resize(m+1, 0);
        for (int p = 1; p <= m; p++){
            long long sum = 0;
            for (int i = p; i <= N; i += m){
                sum += a[i];
            }
            dp[m][p] = sum;
        }
    }
    
    while(Q--){
        int m, p;
        cin >> m >> p;
        long long answer = 0;
        if(m <= B){
            answer = dp[m][p];
        } else {
            for (int i = p; i <= N; i += m){
                answer += a[i];
            }
        }
        cout << answer << "\n";
    }
    
    return 0;
}
