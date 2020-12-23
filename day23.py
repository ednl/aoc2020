def crabcups(labels, moves=100, cups=0, pick=3):
    cups = max(cups, len(labels))
    a = [i for i in range(1, cups + 2)]
    b = [int(c) for c in labels]

    a[0] = a[-1] = b[0]
    for i in range(len(b) - 1):
        a[b[i]] = b[i + 1]
    a[b[len(b) - 1]] = b[0] if cups == len(b) else len(b) + 1

    cur = 0
    for _ in range(moves):
        cur = a[cur]
        nxt = cups if cur == 1 else cur - 1

        up = []
        lastpick = cur
        for _ in range(pick):
            up.append(lastpick := a[lastpick])
        while nxt in up:
            nxt = cups if nxt == 1 else nxt - 1

        tmp = a[lastpick]
        a[lastpick] = a[nxt]
        a[nxt] = a[cur]
        a[cur] = tmp

    if cups < 10:
        s = ''
        i = a[1]
        while i != 1:
            s += str(i)
            i = a[i]
        print(s)
 
    return a[1] * a[a[1]]

# Part 1
crabcups('362981754')

# Part 2
print(crabcups('362981754', moves=10000000, cups=1000000))
