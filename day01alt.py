with open('input01.txt') as f:
    data = sorted(map(int, list(f)))

count = len(data)
target = 2020

def findsum2():
	for i, a in enumerate(data[:count - 1]):
		if a > target:
			break
		for b in data[i + 1:]:
			s = a + b
			if s > target:
				break
			if s == target:
				return a * b

def findsum3():
	for i, a in enumerate(data[:count - 2]):
		if a > target:
			break
		for j, b in enumerate(data[i + 1:count - 1]):
			s1 = a + b
			if s1 > target:
				break
			for c in data[j + 1:]:
				s2 = s1 + c
				if s2 > target:
					break
				if s2 == target:
					return a * b * c

print(findsum2())
print(findsum3())
