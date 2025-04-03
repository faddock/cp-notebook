def main():
    n = int(input())
    a = list(map(int, input().split()))
    op = list(map(str, input().split()))

    dp = [[0] * n for _ in range(n)]
    for i in range(n):
        dp[i][i] = a[i]

    for length in range(2,n+1):
        for l in range(0, n-length+1):
            r = l + length - 1
            temp = float('-inf')
            for k in range(l, r):
                if op[k] == '*':
                    temp = max(temp, dp[l][k] * dp[k+1][r])
                else:
                    temp = max(temp, dp[l][k] + dp[k+1][r])
            dp[l][r] = temp
    
    print(dp[0][n-1])

    # for i in range(n):
    #     for j in range(n):
    #         print(dp[i][j], end=" ")
    #     print("")



if __name__ == "__main__":
    main()

