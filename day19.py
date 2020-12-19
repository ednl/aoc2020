import re
from functools import lru_cache as memoize

isstr = re.compile(r'^(\d+): "([ab])"$')
isnums = re.compile(r'^(\d+): (\d+)( \d+)?( \| (\d+)( \d+)?)?$')

rules = {}
data = []

part = 1
for line in open('day19.txt'):
    line = line.strip()
    if len(line) == 0:
        part += 1
    elif part == 1:
        if m := isstr.match(line):
            rules[int(m.group(1))] = m.group(2)
        if m := isnums.match(line):
            rules[int(m.group(1))] = [-1 if i is None else int(i) for i in m.group(2, 3, 5, 6)]
    elif part == 2:
        data.append(line)


@memoize
def pattern(n):
    if n == -1:
        return ""
    rule = rules[n]
    if isinstance(rule, str):
        return rule
    option1 = pattern(rule[0]) + pattern(rule[1])
    if rule[2] >= 0:
        option2 = pattern(rule[2]) + pattern(rule[3])
        return '(?:' + option1 + '|' + option2 + ')'
    return option1

# Part 1
rulezero = re.compile(pattern(0))
# print(sum([1 if re.fullmatch(rulezero, message) else 0 for message in data]))
print(sum(bool(rulezero.fullmatch(message)) for message in data))

# Part 2
# My rule 0 = 8 11
# New rule 8 = 42 | 42 42 | 42 42 42 | ...
# New rule 11 = 42 31 | 42 42 31 31 | 42 42 42 31 31 31 | ...
# So, my rule 0 = 42{n} 31{m}, where n>m and m>0
# Problem: the number of repeated group matches is not returned by Python's re.match
# but looking at the rule set: every match for one rule must have the same length
# so, "n>m" can be translated as len(42+)/len(42) > len(31+)/len(31)
rulezero = '((' + pattern(42) + ')+)((' + pattern(31) + ')+)'
matches = 0
for message in data:
    fm = re.fullmatch(rulezero, message)
    if fm:
        if len(fm.group(1)) // len(fm.group(2)) > len(fm.group(3)) // len(fm.group(4)):
            matches += 1
print(matches)
