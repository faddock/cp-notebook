from math import gcd
import sys

it = iter(sys.stdin.buffer.read().split())
T = int(next(it))
out = []
for _ in range(T):
    x = int(next(it)); y = int(next(it))
    if gcd(x, y) != 1:
        print(-1)
    else:
        z = x * y - x - y
        print(str(z) if z > 0 else "-1")