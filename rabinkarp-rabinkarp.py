s = input().strip()
n = len(s)
mod = 10**9+7
base = 127

h = [0] * (n+1)
p = [1] * (n+1)
for i, ch in enumerate(s):
    v = ord(ch) - 96
    h[i+1] = (h[i] * base + v) % mod
    p[i+1] = (p[i] * base) % mod

def get_hash(i, L):
    return (h[i+L] - h[i] * p[L]) % mod

ans = 0
for i in range(n):
    for j in range(i+1, n):
        lo, hi = 0, n - j
        while lo <= hi:
            mid = (lo + hi) // 2
            if get_hash(i, mid) == get_hash(j, mid):
                lo = mid + 1
            else:
                hi = mid - 1
        ans += hi

print(ans)