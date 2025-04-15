# lps of (n) = n - L
# L = n - lps(N)
# where L is the output max length

def compute_lps(p):
    m = len(p)
    lps = [0] * m
    j = 0
    i = 1
    while i < m:
        if p[i] == p[j]:
            j += 1
            lps[i] = j
            i += 1
        else:
            if j:
                j = lps[j-1]
            else:
                lps[i] = 0
                i += 1
    return lps

s = input().strip()
lps = compute_lps(s)
L = len(s) - lps[len(s)-1]

print(s[:L])