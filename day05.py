file = list(open('input05.txt'))

hi = 0
seats = []
for line in file:
	id = int(''.join(['1' if c == 'B' or c == 'R' else '0' for c in line.strip()]), 2)
	hi = max(hi, id)
	seats.append(id)

# Part 1
print(hi)

# Part 2
seats.sort()
for ix, id in enumerate(seats, start=seats[0]):
	if ix != id:
		print(id - 1)
		break
