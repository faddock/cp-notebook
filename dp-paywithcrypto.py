
input_data = input().split()
n = int(input_data[0])
w = int(round(float(input_data[1]) * 100))

coins = [int(round(float(x) * 100)) for x in input().split()]
mod = 998244353
dp = [0] * (w + 1)
dp[0] = 1
for coin in coins:
    for i in range(coin, w+1):
        dp[i] += dp[i-coin]
        dp[i] %= mod
 
print(dp[w])

# the secret to solving this is - start with just one coin - and try to solve

'''
Pay With Crypto
Time Limit: 1 Second
Memory Limit: 256 MB
In recent years, as cryptocurrencies become increasingly popular, people are able to pay for products using
them! Each cryptocurrency has its unique value in USD (rounded to one cent). As a crypto enthusiast, you
are interested in how many different combinations of cryptocurrencies can you pay for the product? Two
combinations are said to be different if there is at least one unit difference in any type of cryptocurrency
used. Since the number can be very large, output the answer modulo 998 244 353.
Input
The first line of input contains one integer and one ”two decimal doubles” n and w (1 ≤ n ≤ 100, 0.01 ≤
w ≤ 100.00), as described in the problem statement.
The second line contains n ”two decimal doubles” a1, . . . , an (0.01 ≤ ai ≤ 100.00) - the value of the n types
of cryptocurrencies you can use.
Output
Output the number of combinations you can use modulo 998 244 353.

Sample Inputs
6 9.99
1.00 1.99 3.99 3.00 0.99 10.00

Sample Outputs
10

Note
The ten ways to pay $9.99 are:
• $1.00 × 9 + $0.99 × 1
• $1.00 × 8 + $1.99 × 1
• $1.00 × 6 + $3.00 × 1 + $0.99 × 1
• $1.00 × 6 + $3.99 × 1
• $1.00 × 5 + $3.00 × 1 + $1.99 × 1
• $1.00 × 3 + $3.00 × 2 + $0.99 × 1
• $1.00 × 3 + $3.00 × 1 + $3.99 × 1
• $1.00 × 1 + $3.00 × 2 + $1.99 × 1
• $3.00 × 3 + $0.99 × 1
• $3.00 × 2 + $3.99 × 1
'''