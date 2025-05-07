import math
n, k = map(int, input().split())
points = []
for i in range(n):
    points.append(list(map(int, input().split())))

dist = []
for x, y in points:
    dist.append(math.sqrt(x**2 + y**2))

print(dist)
dist = sorted(dist)
print(dist[k])