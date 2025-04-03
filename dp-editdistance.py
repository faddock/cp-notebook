
s1 = input().strip()
s2 = input().strip()
m, n = len(s1), len(s2)
dp = [[float('inf')]*(n+1) for _ in range(m+1)]

for i in range(m+1):
    dp[i][0] = i
for i in range(n+1):
    dp[0][i] = i

min_count = 0
for i in range(1, m+1):
    for j in range(1, n+1):
        if s1[i-1] == s2[j-1]:
            dp[i][j] = dp[i-1][j-1]
        else:
            dp[i][j] = min(dp[i][j], dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + 1)
print(dp[m][n])

for i in range(n+1):
    for j in range(m+1):
        print(dp[j][i], end= " ")
    print()
