from copy import deepcopy

#    0 1 2 3 4 5 6
# 0: x x x x x x x
# 1:  x x x x x x x
# 2: x x x x x x x
# 3:  x x x x x x x
# 4: x x x x x x x
step = {
    'e' : ( 0,  1),
    'se': ( 1,  0), # c += r % 2
    'sw': ( 1, -1), # c += r % 2
    'w' : ( 0, -1),
    'nw': (-1, -1), # c += r % 2
    'ne': (-1,  0)  # c += r % 2
}

txt = []
with open('input24.txt') as f:
    txt = [line.strip() for line in f]

data = []
i = 0
for s in txt:
    data.append([])
    j = 0
    while j < len(s):
        ch = s[j]
        if ch == 'e' or ch == 'w':
            data[i].append(ch)
            j += 1
        elif ch == 'n' or ch == 's':
            ch += s[j + 1]
            data[i].append(ch)
            j += 2
    i += 1

grid = []
for i in range(101):
    grid.append([0] * 101)

for nav in data:
    r = c = 20
    for bearing in nav:
        odd = r % 2
        dr, dc = step[bearing]
        c += dc + abs(dr) * odd
        r += dr
    grid[r][c] ^= 1

print(sum(map(sum, grid)))

def neighbours(r, c):
    odd = r % 2
    n = grid[r][c - 1] + grid[r][c + 1]
    n += grid[r - 1][c + odd - 1] + grid[r - 1][c + odd]
    n += grid[r + 1][c + odd - 1] + grid[r + 1][c + odd]
    return n

g2 = deepcopy(grid)
for _ in range(100):
    for r in range(1, 100):
        for c in range(1, 100):
            nb = neighbours(r, c)
            if grid[r][c] == 1:
                g2[r][c] = 0 if nb == 0 or nb > 2 else 1
            else:
                g2[r][c] = 1 if nb == 2 else 0
    grid, g2 = g2, grid

# 1899 too low
print(sum(map(sum, grid)))
