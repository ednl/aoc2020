import array

def crabcups(labels, moves=100, cups=0, pick=3):
    cups = max(cups, len(labels))
    a = array.array('I', range(1, cups + 2))
    b = array.array('I', map(int, labels))

    a[0] = a[-1] = b[0]
    for i in range(len(b) - 1):
        a[b[i]] = b[i + 1]
    a[b[len(b) - 1]] = b[0] if cups == len(b) else len(b) + 1

    cur = 0
    for _ in range(moves):
        cur = a[cur]
        nxt = cur - 1 if cur != 1 else cups

        while True:
            i = cur
            found = False
            for _ in range(pick):
                if (i := a[i]) == nxt:
                    found = True
                    nxt = nxt - 1 if nxt != 1 else cups
                    break
            if not found:
                break

        a[i], a[nxt], a[cur] = a[nxt], a[cur], a[i]

    if cups < 10:
        s = ''
        i = a[1]
        while i != 1:
            s += str(i)
            i = a[i]
        print(s)
 
    return a[1] * a[a[1]]

# Part 1
data = '362981754'
crabcups(data)

# Part 2
print(crabcups(data, moves=10000000, cups=1000000))
