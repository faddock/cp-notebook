def compute_lps(p):
    m = len(p)
    lps = [0] * m
    j = 0
    for i in range(1, m):
        while j and p[i] != p[j]:
            j = lps[j - 1]
        if p[i] == p[j]:
            j += 1
            lps[i] = j
    return lps

S = input().strip()
T = input().strip()
lps = compute_lps(T)
res = []
state = []
matched = 0
tlen = len(T)
for ch in S:
    while matched and ch != T[matched]:
        matched = lps[matched - 1]
    if ch == T[matched]:
        matched += 1
    else:
        matched = 0
    res.append(ch)
    state.append(matched)
    if matched == tlen:
        for _ in range(tlen):
            res.pop()
            state.pop()
        matched = state[-1] if state else 0

print("".join(res))


"""
Interception
Time Limit: 1 Second
Memory Limit: 2048 MB
A hostile agent is attempting to send a secret SOS signal to their allies. They have constructed a message
string S (of length at most 106), which may contain multiple occurrences of a specific codeword pattern T.
Your task is to help intercept the signal and remove all instances of this SOS signal T before it can be fully
transmitted.
To do this, whenever the codeword T appears in the signal S, you must immediately delete its first occurrence.
After each deletion, you must check the updated string again and continue deleting T until the signal contains
no instances of the codeword.
Note that deleting one occurrence of T may cause a new occurrence of T to form, so you must keep scanning
from the beginning after every deletion.
Your mission is to output the final version of the intercepted signal string after all codewords have been
removed.
Input
The input consists of two lines:
• The first line contains the string S (the original signal), where 1 ≤|S|≤106
.
• The second line contains the string T (the enemy codeword), where 1 ≤|T |≤106
.
Both strings consist of visible ASCII characters.
Output
Output a single line containing the resulting signal string after all occurrences of the codeword T have been
removed.
Sample Inputs
SOSABCSOSD
SOS

Sample Outputs
ABCD
"""