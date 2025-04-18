n, m = map(int, input().split()) 

mod1 = 10**9 + 5
mod2 = 10**9 + 6
base = 256

dictionary = set()
maxW = 0
for _ in range(m):
    w = input().strip()
    maxW = max(maxW, len(w))
    h1 = h2 = 0
    for c in w:
        o = ord(c)
        h1 = (h1 * base + o) % mod1
        h2 = (h2 * base + o) % mod2
    dictionary.add((h1, h2))


# 2) Read tokens and build the concatenated string S
tokens = input().split()
pos = [0] * (n + 1)
for i in range(n):
    pos[i+1] = pos[i] + len(tokens[i])
S = ''.join(tokens)
L = len(S)

# 3) Compute prefix hashes and base powers for S
H1 = [0] * (L + 1)
H2 = [0] * (L + 1)
P1 = [1] * (L + 1)
P2 = [1] * (L + 1)
for i, ch in enumerate(S):
    o = ord(ch)
    H1[i+1] = (H1[i] * base + o) % mod1
    H2[i+1] = (H2[i] * base + o) % mod2
    P1[i+1] = (P1[i] * base) % mod1
    P2[i+1] = (P2[i] * base) % mod2

# 4) DP over token boundaries
dp = [False for _ in range(n+1)]
back = [None for _ in range(n+1)]
dp[0] = True

for i in range(1, n+1):
    # Only consider j where the total character length ≤ maxW
    for j in range(i-1, -1, -1):
        length = pos[i] - pos[j]
        if length > maxW:
            break
        # rolling hash of S[pos[j]:pos[i]]
        h1 = (H1[pos[i]] - H1[pos[j]] * P1[length]) % mod1
        h2 = (H2[pos[i]] - H2[pos[j]] * P2[length]) % mod2
        if dp[j] and (h1, h2) in dictionary:
            dp[i] = True
            back[i] = j
            break


if not dp[n]:
    print(-1)
else:
    result = []
    cur = n
    while cur > 0:
        j = back[cur]
        result.append(''.join(tokens[j:cur]))
        cur = j
    print(' '.join(reversed(result)))