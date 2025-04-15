s = input().strip()
t = input().strip()


# brute force
# res = 0
# for i in range(len(s)):
#     cnt = 0
#     for j in range(len(t)):

#         if i+j < len(s) and s[i+j] == t[j]:
#            cnt += 1
#     if cnt == len(t):
#         res += 1

# print(res)


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

def kmp_search(s, p):
    n, m = len(s), len(p)
    lps = compute_lps(p)
    print(lps)
    count = i = j = 0
    while i < n:
        if s[i] == p[j]:
            i += 1
            j += 1
        if j == m:
            count += 1
            j = lps[j-1]
        elif i < n and s[i] != p[j]:
            if j:
                j = lps[j-1]
            else:
                i += 1
    return count
print(s)

print(t)
print(kmp_search(s, t))


"""
A. String Matching
time limit per test1 second
memory limit per test256 megabytes
Given two strings 𝑠 and 𝑡, determine the number of times 𝑡 occurs in 𝑠.

Input
The first line contains 𝑠, the second line contains 𝑡. The lines consist only of capital Latin letters, and 1≤|𝑠|,|𝑡|≤300000.

Output
Output the number of times 𝑡 occurs in 𝑠.

Examples
inputCopy
BABABABABABABABAB
ABABAB
outputCopy
6
inputCopy
ACCEPTED
WRONGANSWER
outputCopy
0
inputCopy
ABBBBA
BBB
outputCopy
2

"""
         