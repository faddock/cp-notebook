MOD = 998244353

T = int(input())
tests = [tuple(map(int, input().split())) for _ in range(T)]

max_n = max(n + m for _, n, m in tests)
fact = [1] * (max_n + 1)
for i in range(1, max_n + 1):
    fact[i] = fact[i - 1] * i % MOD

inv_fact = [1] * (max_n + 1)
inv_fact[max_n] = pow(fact[max_n], MOD - 2, MOD)
for i in range(max_n, 0, -1):
    inv_fact[i - 1] = inv_fact[i] * i % MOD

def C(n, r):
    return 0 if r < 0 or r > n else fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD

for k, n, m in tests:
    if n > k + m:  
        print(0)
        continue
    total = C(n + m, n)
    bad   = C(n + m, n - k - 1) if n >= k + 1 else 0
    good  = (total - bad) % MOD
    ans   = good * fact[n] % MOD * fact[m] % MOD
    print(ans)