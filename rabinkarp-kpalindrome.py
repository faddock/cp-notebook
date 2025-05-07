import sys

n, k = map(int, input().split())
s = input().strip()
sr = s[::-1]

BASE = 1315423911
MASK = (1 << 64) - 1

powb = [1] * (n + 1)
for i in range(1, n + 1):
    powb[i] = (powb[i - 1] * BASE) & MASK

f = [0] * (n + 1)
fr = [0] * (n + 1)
for i in range(n):
    f[i + 1] = (f[i] * BASE + ord(s[i])) & MASK
    fr[i + 1] = (fr[i] * BASE + ord(sr[i])) & MASK

get_f  = lambda l, r: (f[r + 1]  - f[l]  * powb[r - l + 1]) & MASK
get_fr = lambda l, r: (fr[r + 1] - fr[l] * powb[r - l + 1]) & MASK

ans = 0
for i2 in range(0, n - k - 1):
    maxd = min(i2 + 1, n - (i2 + k + 1))
    lo = 0
    hi = maxd + 1
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        l1 = i2 - mid + 1
        r1 = i2
        l2 = i2 + k + 1
        r2 = i2 + k + mid
        sr_l = n - 1 - r2
        sr_r = n - 1 - l2
        if get_f(l1, r1) == get_fr(sr_l, sr_r):
            lo = mid
        else:
            hi = mid
    ans += lo

print(ans)