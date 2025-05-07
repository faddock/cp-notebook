MOD = 998244353
MAX = 1000

fact = [1] * (MAX + 1)
for i in range(1, MAX + 1):
    fact[i] = fact[i - 1] * i % MOD

inv = [1] * (MAX + 1)
inv[MAX] = pow(fact[MAX], MOD - 2, MOD)
for i in range(MAX, 0, -1):
    inv[i - 1] = inv[i] * i % MOD

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    ans = 0
    for miss in range(11):
        sym = 11 - miss
        if sym == 0:
            continue
        df = fact[10] * inv[miss] % MOD * inv[10 - miss] % MOD
        if miss & 1:
            df = MOD - df
        big = pow(sym, n * m, MOD)
        invm = pow(sym, MOD - 1 - m, MOD)
        invn = pow(sym, MOD - 1 - n, MOD)
        rowpow = 1
        acc = 0
        for r in range(n + 1):
            choose = fact[n] * inv[r] % MOD * inv[n - r] % MOD
            if r & 1:
                choose = MOD - choose
            choose = choose * pow(invm, r, MOD) % MOD
            factor = rowpow * invn % MOD
            term = pow((1 - factor) % MOD, m, MOD)
            acc = (acc + choose * term) % MOD
            rowpow = rowpow * sym % MOD
        ans = (ans + df * big % MOD * acc) % MOD
    print(ans)