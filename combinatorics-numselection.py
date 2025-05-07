MOD = 998244353

T = int(input())
cases = []
mx = 0
for _ in range(T):
    n, k = map(int, input().split())
    cases.append((n, k))
    if n > mx:
        mx = n
    if n + k - 1 > mx:
        mx = n + k - 1

fact = [1] * (mx + 1)
for i in range(1, mx + 1):
    fact[i] = fact[i - 1] * i % MOD

inv_fact = [1] * (mx + 1)
inv_fact[mx] = pow(fact[mx], MOD - 2, MOD)
for i in range(mx, 0, -1):
    inv_fact[i - 1] = inv_fact[i] * i % MOD

for n, k in cases:
    p1 = fact[n] * inv_fact[n - k] % MOD
    p2 = fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD
    p3 = pow(n, k, MOD)
    p4 = fact[n + k - 1] * inv_fact[k] % MOD * inv_fact[n - 1] % MOD
    print(p1, p2, p3, p4)