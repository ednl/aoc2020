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
        edges[id] = [list(map(lambda x: int(x, 2), bits))]  # 0 = original tile
        edges[id].append(fhor(edges[id][0]))                # 1 = flipped tile
        for _ in range(3):
            edges[id].append(rotl(edges[id][-2]))           # 2,4,6 = rotated from original
            edges[id].append(rotl(edges[id][-2]))           # 3,5,7 = rotated from flipped

# For tile t1 oriented as p1, find its neighbour in direction d1,
# return that tile number and orientation
def neighbour(t1, p1, d1):
    e1 = edges[t1][p1]
    d2 = (d1 + 2) % 4
    for t2 in edges:
        if t2 != t1:
            for p2, e2 in enumerate(edges[t2]):
                if e1[d1] == e2[d2]:
                    return (t2, p2)
    return None

def findcorners():
    for t in edges:
        n = p = 0
        for d in range(4):
            p <<= 1
            if neighbour(t, 0, d):
                p |= 1
                n += 1
        if n == 2:
            if p == 9:
                yield t, 0  # original orientation
            elif p == 12:
                yield t, 2  # 1x rotl
            elif p == 6:
                yield t, 4  # 2x rotl
            elif p == 3:
                yield t, 6  # 3x rotl

# Part 1
# Orientation is not used for part 1, and I'm going to redo the
# whole thing for part 2, soooo, could have been shorter :shrug: 
corners = list(findcorners())  # [(2693, 0), (1549, 0), (3539, 4), (3709, 6)]
print(prod([t for t, _ in corners]))
