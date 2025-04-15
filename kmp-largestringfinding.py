def main():
    import sys
    T = sys.stdin.read().strip()
    n = len(T)
    ans = [0] * n
    i, j, k = 0, 1, 0
    ans[0] = 0
    for r in range(1, n):
        while j <= r:
            while j + k <= r and i + k <= r and T[i + k] == T[j + k]:
                k += 1
            if j + k > r:
                break
            if T[i + k] < T[j + k]:
                i = j
                j = i + 1
                k = 0
            else:
                j = j + k + 1
                k = 0
        ans[r] = i
        if r == j: 
            j += 1
    out = []
    for r, start in enumerate(ans):
        out.append(f"{start+1} {r+1}")
    print("\n".join(out))

if __name__ == "__main__":
    main()


"""
C. Large String Finding
time limit per test2 s
memory limit per test256 MB
For a given string, find the lexicographically largest substring of every prefix and output its left and right index. If there are many occurrences of the same substring, output the leftmost one.

Input
The only line contains a string 𝑇 (1≤|𝑇|≤106), which consists of lowercase letters, a to z.

Output
Output |𝑇| lines. The 𝑖-th line should contain two integers 𝑙𝑖 and 𝑟𝑖, representing the answer for the prefix of length 𝑖.

Examples
inputCopy
potato
outputCopy
1 1
1 2
3 3
3 4
3 5
5 6
inputCopy
pbpbppb
outputCopy
1 1
1 2
1 3
1 4
1 5
5 6
5 7
"""