from copy import deepcopy

c2n = {'.': -1, 'L': 0, '#': 1}
n2c = {v: k for k, v in c2n.items()}

a = []
with open('input11.txt') as f:
	for line in f:
		a.append([-1] + [c2n[c] for c in line.strip()] + [-1])

w = len(a[0])
a.append([-1]*w)
a.insert(0, [-1]*w)
h = len(a)

b = deepcopy(a)
c = deepcopy(a)

def debug(a):
	for row in a:
		print(''.join([n2c[seat] for seat in row]))

def occupied(a1):
	n = 0
	for row in a1:
		for seat in row:
			if seat == 1:
				n += 1
	return n

def around1(a1, row, col):
	n = -1 if a1[row][col] == 1 else 0
	for r in range(row - 1, row + 2):
		for c in range(col - 1, col + 2):
			if a1[r][c] == 1:
				n += 1
	return n

def evolve1(a1, a2):
	changed = False
	for r in range(1, h - 1):
		for c in range(1, w - 1):
			p = a1[r][c]
			if p >= 0:
				n = around1(a1, r, c)
				if (p == 0 and n == 0) or (p == 1 and n >= 4):
					a2[r][c] = 1 - p
					changed = True
				else:
					a2[r][c] = p
	return changed

while evolve1(b, a):
	b, a = a, b

print('Part 1:', occupied(b))

def around2(a1, row, col):
	n = 0
	for i in range(-1, 2):
		for j in range(-1, 2):
			if i or j:
				r = row + i
				c = col + j
				occ = False
				while not occ and r > 0 and r < h - 1 and c > 0 and c < w - 1:
					if a1[r][c] == 0:
						break
					occ = a1[r][c] == 1
					r += i
					c += j
				if occ:
					n += 1
	return n

def evolve2(a1, a2):
	changed = False
	for r in range(1, h - 1):
		for c in range(1, w - 1):
			p = a1[r][c]
			if p >= 0:
				n = around2(a1, r, c)
				if (p == 0 and n == 0) or (p == 1 and n >= 5):
					a2[r][c] = 1 - p
					changed = True
				else:
					a2[r][c] = p
	return changed

while evolve2(c, a):
	c, a = a, c

print('Part 2:', occupied(c))
