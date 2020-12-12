with open('input12.txt') as f:
	data = [(line[:1], int(line[1:])) for line in f]

heading = {'E': (1,0), 'N': (0,1), 'W': (-1,0), 'S': (0,-1)}

def nav(wx, wy, part):
	x = y = 0
	for action, value in data:
		if action == 'F':
			x += value * wx
			y += value * wy
		elif action == 'L' or action == 'R':
			if action == 'R':
				value = 360 - value
			while value:
				wx, wy = -wy, wx
				value -= 90
		else:
			dx, dy = [value * i for i in heading[action]]
			if part == 1:
				x += dx
				y += dy
			else:
				wx += dx
				wy += dy
	return abs(x) + abs(y)

print(nav(*heading['E'], part=1))
print(nav(10, 1, part=2))
