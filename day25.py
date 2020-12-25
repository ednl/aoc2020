# My version: pick the smallest loop
def secret1(p, q):
    e, k, b, m = 0, 1, 7, 20201227
    while k != p and k != q:
        k = k * b % m
        e += 1
    b = p if k == q else q
    return pow(b, e, m)

# Version by @wfxr looks neat, from
# https://www.reddit.com/r/adventofcode/comments/kjtg7y/2020_day_25_solutions/ggz4pxw/
# but why would finding a smaller modpow take fewer loops? @mebeim writes at
# https://www.reddit.com/r/adventofcode/comments/kjtg7y/2020_day_25_solutions/ggz4bpl/ :
# "Given the public base g = 7, the public modulo p = 20201227, and the two public keys A and B
# (obtained as A = g^a mod p, B = g^b mod p), calculate the secret key s = A^b mod p = B^a mod p."
# So in other words: why would a < b if A < B?
def secret2(p, q):
    r, k, b, m = 1, 1, 7, 20201227
    if p > q:  # why??
        p, q = q, p
    while k != p:
        k = k * b % m
        r = r * q % m
    return r

# Combined version is the fastest
def secret3(p, q):
    e, k, b, m = 0, 1, 7, 20201227
    if p > q:
        p, q = q, p
    while k != p:
        k = k * b % m
        e += 1
    return pow(q, e, m)

pubkeys = 15113849, 4206373
print(secret1(*pubkeys))
print(secret2(*pubkeys))
print(secret3(*pubkeys))
