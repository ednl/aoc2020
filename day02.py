#!/usr/bin/env python3

with open('input02.txt', 'rt') as f:
	txt = list(f)

bad = 0
good = 0
for line in txt:
	fields = line.split()
	limit = list(map(int, fields[0].split('-')))
	char = fields[1].strip(':')
	pwd = fields[2]
	n = pwd.count(char)
	if n < limit[0] or n > limit[1]:
		bad += 1
	if (pwd[limit[0] - 1] == char) != (pwd[limit[1] - 1] == char):
		good += 1

print('bad:', bad)
print('good:', good)
