from operator import add

data = list(open('input03.txt'))
width = len(data[0].strip())

slopes = [[1,1], [3,1], [5,1], [7,1], [1,2]]
prod = 1

for slope in slopes:
	pos = [0, 0]
	sum = 0
	while pos[1] < len(data):
		sum += 1 if data[pos[1]][pos[0] % width] == '#' else 0
		pos = list(map(add, pos, slope))
	prod *= sum
	print(slope, sum)

print(prod)
