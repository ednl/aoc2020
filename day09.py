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

# Part 2
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
		print(min(a[i:j]) + max(a[i:j]))
		break
