INF = 10 ** 9
SZ  = 26
pc  = int.bit_count

n = int(input())
wds = []
while len(wds) < n:
    wds.extend(input().split())
wds = wds[:n]

tot = 0
g   = [[INF] * SZ for _ in range(SZ)]
out = [0] * SZ
inn = [0] * SZ
for i in range(SZ):
    g[i][i] = 0

for w in wds:
    a = ord(w[0].lower()) - 97
    b = ord(w[-1].lower()) - 97
    l = len(w)
    tot += l
    if l < g[a][b]:
        g[a][b] = l
    out[a] += 1
    inn[b] += 1

for k in range(SZ):
    gk = g[k]
    for i in range(SZ):
        dik = g[i][k]
        if dik == INF:
            continue
        gi = g[i]
        for j in range(SZ):
            nd = dik + gk[j]
            if nd < gi[j]:
                gi[j] = nd

pos = [v for v in range(SZ) if out[v] > inn[v]]
neg = [v for v in range(SZ) if inn[v] > out[v]]
best = INF

for s in [None] + pos:
    if s is not None and out[s] <= inn[s]:
        continue
    for t in [None] + neg:
        if t is not None and inn[t] <= out[t]:
            continue
        if s is None and t is None and (pos or neg):
            continue

        bal = [out[i] - inn[i] for i in range(SZ)]
        if s is not None:
            bal[s] -= 1
        if t is not None:
            bal[t] += 1

        vn = [i for i in range(SZ) for _ in range(-bal[i]) if bal[i] < 0]
        vp = [i for i in range(SZ) for _ in range( bal[i]) if bal[i] > 0]
        if len(vn) != len(vp):
            continue
        m = len(vn)
        if m == 0:
            best = min(best, tot)
            continue

        cst = [[g[vn[i]][vp[j]] for j in range(m)] for i in range(m)]
        dp  = [INF] * (1 << m)
        dp[0] = 0
        for mask in range(1 << m):
            i = pc(mask)
            if i == m:
                continue
            for j in range(m):
                if mask >> j & 1:
                    continue
                nmask = mask | (1 << j)
                val   = dp[mask] + cst[i][j]
                if val < dp[nmask]:
                    dp[nmask] = val

        best = min(best, tot + dp[-1])

print(best)