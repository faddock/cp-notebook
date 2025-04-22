# two integers given a and b - find the GCD of a and b
# input q: - number of queries
# next q lines - a, b each - find gcd - guaranteed that a and b will not both equal to 0
# the greatest common factor number that divides them exactly
def gcd(a, b):
    if a == 0:
        return b
    if b == 0:
        return a
    i = 1
    res = 1
    while i <= min(a, b):
        i += 1
        if a % i == 0 and b % i == 0:
            res = i
    return res

def gcd_fast(a, b):
    while b != 0:
        a, b = b, a % b
    return a


q = int(input().strip())
while q:
    q -= 1
    a, b = [int(x) for x in input().split()]
    print(gcd_fast(a, b))

        
