# how many fractions x/y written in decimal form have a finite number of digits where 1 <= x, y <= n?
# input only consists of one integer n
# output one integer

n = int(input().strip())
ans = 0
for y in range(1, n+1):
    t = y
    while t % 2 == 0:
        t //= 2
    while t % 5 == 0:
        t //= 5
    ans += n // t
print(ans)

