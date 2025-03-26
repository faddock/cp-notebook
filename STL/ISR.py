'''
ISR
Time Limit: 1 Second
Memory Limit: 256 MB
LetianPie is tired of eating McDonald’s and Burger King everday, so he decided to go to Illinois Street
Residence Hall (ISR) Dining Center for dinner today. Today, ISR provides n different kinds of food, with
i-th kind of food served on the i-th table, and all tables are arranged in a line. Each person can choose to
get in line at i-th table, and leave the line at j-th table (i ≤ j), grabbing all kinds of food between i-th table
and j-th table (inclusive). Each person can only get in line once.
Before deciding what kinds of food to eat tonight, LetianPie first assigns each kind of food an integer value
denoting how much he likes this kind of food. Specifically, the i-th kind of food is assigned with value ai
(−10^5 ≤ ai ≤ 10^5), where a positive value indicates that LetianPie likes this kind of food, and vice versa.
The happiness LetianPie gains from the dinner is the sum of values assigned to the foods he picks. Now
LetianPie is wondering the maximum happiness he can gain from the dinner if he chooses the starting and
ending tables optimally. Since he is too hungry to think about it, he asks you to help him out.
Input
The first line contains a single integer n (1 ≤ n ≤ 10^5) - the number of foods provided by ISR.
The second line contains n integer a1, . . . , an (−10^5 ≤ ai ≤ 10^5) - how much LetianPie likes each kind of
food.
Output
Output a single integer denoting the maximum happiness LetianPie can gain from the dinner.
'''

import sys


def ISR(food_ratings):
    max_val = 0
    max_prev = 0

    for i in range(len(food_ratings)):
        max_prev = max(food_ratings[i], max_prev+food_ratings[i])
        max_val = max(max_prev, max_val)

    return(max_val)


if __name__ == "__main__":
    n = int(sys.stdin.readline().strip())
    food_ratings = list(int(i) for i in sys.stdin.readline().strip().split())
    sys.stdout.write(str(ISR(food_ratings)) + "\n")
