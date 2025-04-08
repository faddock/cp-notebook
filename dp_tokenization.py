n, m = map(int, input().split()) # number of tokens in the input

dictionary = set()
tokens = []

for i in range(1, int(m)+1):
    dictionary.add(input())
tokens.extend(input().split())

dp = [False for _ in range(n+1)]
path = [None for _ in range(n+1)]
dp[0] = True
for i in range(1, n+1):
    for j in range(i):
        if dp[j]: # if all the words till here are true
            word = ''.join(tokens[j:i])
            if word in dictionary:
                dp[i] = True
                path[i] = j
                break

if dp[n]:
    result = []
    idx = n
    while idx > 0:
        j = path[idx]
        result.append(''.join(tokens[j:idx]))
        idx = j
    print(' '.join(reversed(result)))
else:
    print(-1)

# print(dp)
# print(path)
    
# trick to solving this is have a dp array with booleans to decide whetehr to take each token or not
# also maintain path of indeices to reverse and calculate full string