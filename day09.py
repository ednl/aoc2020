from collections import deque
from itertools import combinations

with open('input09.txt') as f:
	a = [int(line) for line in f]

qlen = 25
mynum = 0

# Part 1
q = deque(a[:qlen], maxlen=qlen)
for n in a[qlen:]:
	s = 0
	for duo in combinations(q, 2):
		s = sum(duo)
		if s == n:
			break
	if s != n:
		mynum = n
		break
	q.append(n)

print(mynum)

# Part 2: fastest
# This first checks all starting points for a certain width,
# then goes to the next width.
def weakness1():
	s1 = a[0]
	for slicelen in range(2, len(a)):
		i = 0
		j = slicelen
		s2 = s1 = s1 + a[j - 1]
		while s2 != mynum and j < len(a):
			s2 = s2 - a[i] + a[j]
			i += 1
			j += 1
		if s2 == mynum:
			return min(a[i:j]) + max(a[i:j])
print(weakness1())

# Part 2, simpler but about 2.5-3x as slow
# This first checks all widths from a certain starting point,
# then goes to the next starting point.
def weakness2():
	for i in range(len(a) - 1):
		s = amin = amax = a[i]
		for j in range(i + 1, len(a)):
			s += a[j]
			# Incorrect check because input is not sorted,
			# but it still gives the right result for my input
			# and makes it almost as fast as alternative 1.
			# if s > mynum:
			# 	break
			if a[j] < amin:
				amin = a[j]
			if a[j] > amax:
				amax = a[j]
			if s == mynum:
				return amin + amax
print(weakness2())
