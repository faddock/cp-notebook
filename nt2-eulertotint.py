import sys

MOD = 998244353  # not used here, but in case of consistency?

buf = sys.stdin.buffer.read().split()
t = int(buf[0])
vals = list(map(int, buf[1:]))
mx = max(vals) if vals else 0

phi = list(range(mx + 1))
for i in range(2, mx + 1):
    if phi[i] == i:
        for j in range(i, mx + 1, i):
            phi[j] -= phi[j] // i

out = []
for n in vals:
    print(str(phi[n]))
