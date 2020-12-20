# Permutations:
# orig  : t,r,b,l
# rotl  : r,-b,l,-t | -b,-l,-t,-r | -l,t,-r,b
# fhor  : -t,l,-b,r
# fh+rl : l,b,r,t | b,-r,t,-l | -r,-t,-l,-b

def rev(n):
    s = '{0:010b}'.format(n)
    return int(s[::-1], 2)

def rotl(e):
    return [e[1], rev(e[2]), e[3], rev(e[0])]

def fhor(e):
    return [rev(e[0]), e[3], rev(e[2]), e[1]]

edges = {}
place = {}

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

def find_right(t1, p1):
    e1 = edges[t1][p1]
    for t2 in edges:
        if t2 != t1:
            for p2, e2 in enumerate(edges[t2]):
                if e1[1] == e2[3]:
                    return (t2, p2)
    return (-1, -1)

t1 = tile_ids[0]
p1 = 0
t2, p2 = find_right(t1, p1)
print(t2, p2)
