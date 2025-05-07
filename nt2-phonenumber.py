from collections import deque
import sys

N                 = int(sys.stdin.readline().strip())
a, p              = map(int, sys.stdin.readline().split())
S                 = sys.stdin.readline().strip()
digits            = [int(c) for c in S]

queue   = deque([0])
parent  = [-1]*(N+1)
visited = [False]*(N+1)
visited[0] = True

while queue and not visited[N]:
    i   = queue.popleft()
    cur = 0
    seen = set()
    for j in range(i, N):
        cur = (cur*10 + digits[j]) % p
        if cur in seen:                      # remainder started repeating
            break
        seen.add(cur)

        if cur == a and not visited[j+1]:
            visited[j+1] = True
            parent [j+1] = i
            queue .append(j+1)
            if j+1 == N: break

if not visited[N]:
    print("NO")
    sys.exit()

# reconstruct
cuts = []
idx  = N
while idx:
    prev = parent[idx]
    cuts.append(S[prev:idx])
    idx = prev
cuts.reverse()

print("YES")
print(len(cuts))
print("\n".join(cuts))