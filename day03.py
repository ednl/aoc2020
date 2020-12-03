#!/usr/bin/env python3

with open('input03.txt', 'rt') as f:
	treemap = list(f)

# Where are the trees in the input file
def istree(x, y):
	return 1 if treemap[y][x] == '#' else 0

dimx = len(treemap[0].strip())  # strip EOL '\n'
dimy = len(treemap)             # number of lines
prod = 1                        # answer to part 2

# dx,dy pairs (3,1 was part 1)
slopes = [[1,1], [3,1], [5,1], [7,1], [1,2]]

for slope in slopes:
	dx, dy = slope
	x = 0
	y = 0
	trees = 0
	while y < dimy:
		trees += istree(x, y)
		x = (x + dx) % dimx
		y += dy
	prod *= trees
	print(dx, dy, trees)  # slope and number of trees

print(prod)  # product of the tree numbers on all the slopes
