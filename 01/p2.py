#!/bin/python

import sys
from collections import Counter

l1, l2 = zip(*[line.split() for line in sys.stdin])

l1 = map(int, l1)
l2 = map(int, l2)
l2count = Counter(l2)

r = sum([i*l2count[i] for i in l1])

print(r)

