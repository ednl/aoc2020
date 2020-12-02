#!/usr/bin/env python3

import numpy as np

n = np.sort(np.loadtxt('./git/aoc2020/input01.txt', dtype=np.uint32))
t = 2020

i = 0
while i < len(n) - 1:
	j = i + 1
	while j < len(n):
		s = n[i] + n[j]
		if s > t:
			break
		if s == t:
			print("2:", n[i] * n[j])
			break
		j += 1
	if s == t:
		break
	i += 1

i = 0
while i < len(n) - 2:
	j = i + 1
	while j < len(n) - 1:
		k = j + 1
		while k < len(n):
			s = n[i] + n[j] + n[k]
			if s > t:
				break
			if s == t:
				print("3:", n[i] * n[j] * n[k])
				break
			k += 1
		if s == t:
			break
		j += 1
	if s == t:
		break
	i += 1
