data = '362981754'
pick = 3

def crabcup(moves):
    p = 0
    for _ in range(moves):
        cur = a[p]
        nxt = (cur - 1) % mod

        i = (p + 1) % mod
        found = True
        while found:
            found = False
            j = i
            for _ in range(pick):
                if a[j] == nxt:
                    found = True
                    nxt = (nxt - 1) % mod
                    break
                else:
                    j = (j + 1) % mod

        q = (p + 1 + pick) % mod
        while a[q] != nxt:
            q = (q + 1) % mod

        i = (p + 1) % mod
        for _ in range(pick):
            j = i
            tmp = a[j]
            while j != q:
                k = (j + 1) % mod
                a[j] = a[k]
                j = k
            a[q] = tmp
        p = (p + 1) % mod

# Part 1
a = [int(ch) - 1 for ch in data]
mod = len(a)
crabcup(100)
s = ''
p = (a.index(0) + 1) % mod
for _ in range(mod - 1):
    s += str(a[p] + 1)
    p = (p + 1) % mod
print(s)

# Part 2
# mod  mov1
for mod in range(9, 10):
    for mov in range(100, 101):
        a = [i for i in range(mod)]
        for i, ch in enumerate(data):
            a[i] = int(ch) - 1
        crabcup(mov)
        p = (a.index(0) + 1) % mod
        q = (p + 1) % mod
        print(mod, mov, (a[p] + 1) * (a[q] + 1))
