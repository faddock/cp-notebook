#include <iostream>
#include<bitset>
using namespace std;

int main() {
    int n, b1, b2;
    cin >> n >> b1 >> b2;
    int out;
    if (n == 2) {
        out = b1 + b2;
    } else {
        out = b1 | b2;
    }
    cout << out << "\n";
    return 0;
}



/*
Wolves and Sheep
Time Limit: 1 Second
Memory Limit: 1024 MB
There are n wolves preparing to eat a sheep. Before doing so, two of the wolves decided to give the sheep a
challenge, and set it free if the sheep solved it correctly.
Each of the n wolves has a favorite number, where ai (0 ≤ ai ≤ 230) is the favorite number of the i-th wolf.
The first wolf tells the sheep the result after xor-ing every number except his own. The second wolf also
tells the sheep the number after xor-ing every number except his own.
Now, the sheep needs to figure out what the minimum possible sum of all the wolves’ numbers is.
As the farmer, you want to save your sheep, and you know that your sheep obviously cannot solve this. Help
your sheep answer the question.
Input
The first line contains the integer n (2 ≤ n ≤ 106), denoting the number of wolves.
The second line contains one integer b1 (0 ≤ b1 < 231), the number that the first wolf said.
The third line contains one integer b2 (0 ≤ b2 < 231), the number that the second wolf said.
Output
Output a single integer, denoting the minimum possible sum.

Solution explanation:
if you try on 3 inputs, you observe that to acheive min output, you basically do an or operation or b1 and b2. 
since this calculation is independent of n, you deduce that for n>=3 to 106, you can do or on a and b to get answer
now for n = 2, which is the edge case - you realize that you need to simply add both values.
one misconception is that you have to convert ints to binary to compute the or operator
*/
