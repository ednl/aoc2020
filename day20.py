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

img = []
for _ in range(25):
    img.append([0] * 25)

# Put the first tile in the middle
img[12][12] = edges.keys()[0]

# def matchlr(left, right):
#     return edges[left][1] == edges[right][3]

# def matchtb(top, bottom):
#     return edges[top][2] == edges[bottom][0]

def fit(t1, r, c):
    if r < 24:
        t2 = img[r + 1][c]
        if not matchlr(t1, t2):
            return False
