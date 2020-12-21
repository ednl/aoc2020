from math import prod

# Reverse a 10-bit binary number
def rev(n):
    s = '{0:010b}'.format(n)
    return int(s[::-1], 2)

# Original: t,r,b,l (=top,right,bottom,left)
# Rotations: r,-b,l,-t | -b,-l,-t,-r | -l,t,-r,b
def rotl(e):
    return [e[1], rev(e[2]), e[3], rev(e[0])]

# Flipped horizontally: -t,l,-b,r
# Rotations: l,b,r,t | b,-r,t,-l | -r,-t,-l,-b
def fhor(e):
    return [rev(e[0]), e[3], rev(e[2]), e[1]]

edges = {}
with open('input20.txt') as f:
    tiledata = f.read().replace('#', '1').replace('.', '0').strip().split('\n\n')
    for td in tiledata:
        s = td.strip().split('\n')
        id = int(s[0][5:-1])
        bits = [s[1], ''.join([r[-1] for r in s[1:]]), s[-1], ''.join([r[0] for r in s[1:]])]
        edges[id] = [list(map(lambda x: int(x, 2), bits))]
        for _ in range(3):
            edges[id].append(rotl(edges[id][-1]))
        edges[id].append(fhor(edges[id][0]))
        for _ in range(3):
            edges[id].append(rotl(edges[id][-1]))
        
def neighbour(t1, p1, d1):
    e1 = edges[t1][p1]
    d2 = (d1 + 2) % 4
    for t2 in edges:
        if t2 != t1:
            for p2, e2 in enumerate(edges[t2]):
                if e1[d1] == e2[d2]:
                    return (t2, p2)
    return None

def corner_ids():
    tot = 0
    for t in edges:
        n = 0
        for d in range(4):
            if neighbour(t, 0, d):
                n += 1
                if n > 2:
                    break
        if n == 2:
            yield t
            tot += 1
            if tot == 4:
                return

# Part 1
print(prod(corner_ids()))
