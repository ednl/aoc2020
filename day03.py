data = list(open('input03.txt'))
width = len(data[0].strip())

slope = [[1,1], [3,1], [5,1], [7,1], [1,2]]
product = 1

for dx, dy in slope:
	x = y = trees = 0
	while y < len(data):
		if data[y][x % width] == '#':
			trees += 1
		x += dx
		y += dy
	product *= trees
	print(dx, dy, trees)

print(product)
