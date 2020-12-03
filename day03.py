#!/usr/bin/env python3

with open('input03.txt', 'rt') as f:
	data = list(f)  # map of trees

# Where are the trees in the input file?
def tree(x, y):
	return 1 if data[y][x] == '#' else 0

w = len(data[0].strip())  # width = chars on a line minus EOL
h = len(data)             # height = number of lines
p = 1                     # product = answer to part 2

# All [dx,dy] pairs for part 2 (part 1 was [3,1])
slopes = [[1,1], [3,1], [5,1], [7,1], [1,2]]

for slope in slopes:
	dx, dy = slope
	x = y = n = 0  # start at top-left, n = count the trees
	while y < h:
		n += tree(x % w, y)  # is there a tree here?
		x += dx              # move horizontally
		y += dy              # move vertically
	p *= n            # multiply the numbers of trees
	print(dx, dy, n)  # show slope and number of trees

print(p)  # product of the tree numbers on all the slopes
