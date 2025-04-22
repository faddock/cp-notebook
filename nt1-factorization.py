# prime factorzation - express a whole number as a product of its prime factors
# k
# find the number of prime numbers - O(n)
# example - 5 factorial - 1 times 2 times 3 times 4 times 5
# 1, 2, 3, 4, 5

'''
overview of prime numbers in comeptitive programming
1) find all prime numbers in less than n in O(N) time - Euler's Seive
2) how many numbers from 1 to N?
    f(N) : # of primes from 1 to N
    f(N) proportional to /frac{N}{ln(N)}
    f(10^7) proportioanl to 10^7 / ln(10^7) = 5 times 10^5
'''
'''
brute force
 for i = 1 to n
    factor(n)

where factor:
    for i = 2 .. n
runtime O(n^2)

solution:

'''
# brute force
# for i = 1 to n
# precomputation
# apparently factorization only needs to go to sqrt of n
# take floor of n / 2, n/4 and n/8 - you'll get teh primes
# 
# 26
# 2 13
# 13 1
# 1 2 3 4 5 6 7
# 2^4 × 3^2 × 5^1 × 7^1
# first do primes find - O(N)
# second: for prime < N:
# ans[prime] += N //prime
# prime *= ori_prime
# 

'''
Euler sieve
for (i = 2, i <= n, ++i)
    if S[i] is 0 
    i is a prime
    for (j = i + 1; j <= N; j += 1)
        s[j] = 1

Each non-prime number is sieved by y such that there  is x = cy  where c is its smallest prime number
'''

import sys
n = int(input().strip())
is_comp = bytearray(n+1)
primes = []
for i in range(2, n+1):
    if not is_comp[i]:
        primes.append(i)
    for p in primes:
        ip = i * p
        if ip > n:
            break
        is_comp[ip] = 1
        if i % p == 0:
            break
print(len(primes))
for p in primes:
    cnt = 0
    m = n
    while m:
        m //= p
        cnt += m
    print(p, cnt)