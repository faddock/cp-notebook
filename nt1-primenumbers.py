n = int(input().strip())
is_comp = bytearray(n+1)
primes = []
for i in range(2, n+1):
    if not is_comp[i]:
        primes.append(str(i))
    for p in primes:
        ip = i * int(p)
        if ip > n:
            break
        is_comp[ip] = 1
        if i % int(p) == 0:
            break

print(len(primes))
print(" ".join(primes))


# copy paste in the tempalte for sieve - onyl 5 lines long