#!/bin/python

import sys

l1, l2 = zip(*[line.split() for line in sys.stdin])

l1 = sorted(map(int, l1))
l2 = sorted(map(int, l2))

r = sum([abs(i1-i2) for i1, i2 in zip(l1, l2)])

print(r)
