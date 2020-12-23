data = '362981754'
pick = 3

def crabcup1(moves):
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
crabcup1(100)
s = ''
p = (a.index(0) + 1) % mod
for _ in range(mod - 1):
    s += str(a[p] + 1)
    p = (p + 1) % mod
print(s)

# Part 2
mod = 9
mov = 100

a = [i for i in range(1, mod + 1)]
a[mod - 1] = 0

b = [int(c) - 1 for c in data]
for i in range(len(b) - 1):
    a[b[i]] = b[i + 1]
a[b[-1]] = b[0]

cur = b[0]
nxt = mod - 1 if cur == 0 else cur - 1

nextinpick = True
while nextinpick:
    nextinpick = False
    i = a[cur]
    for _ in range(pick):
        if i == nxt:
            nextinpick = True
            nxt = mod - 1 if cur == 0 else nxt - 1
            break
        else:
            i = a[i]
