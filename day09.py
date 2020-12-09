from collections import deque

with open('input09.txt') as f:
	a = [int(line) for line in f]

qlen = 25
mynum = 0

# Part 1
q = deque(a[:qlen])
for n in a[qlen:]:
	s = 0
	for i in range(qlen - 1):
		for j in range(i + 1, qlen):
			s = q[i] + q[j]
			if s == n:
				break
		if s == n:
			break
	if s != n:
		mynum = n
		break
	q.popleft()
	q.append(n)
print(mynum)

# Part 2
s1 = a[0]
for slicelen in range(2, len(a)):
	i = 0
	j = slicelen
	s1 += a[j - 1]
	s2 = s1
	while s2 != mynum and j < len(a):
		s2 = s2 - a[i] + a[j]
		i += 1
		j += 1
	if s2 == mynum:
		print(min(a[i:j]) + max(a[i:j]))
		break
