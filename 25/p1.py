#!/bin/python

import sys

lockSchematics = map(lambda l: l.strip(), sys.stdin)
lockSchematics = "|".join(lockSchematics).split("||")

locks = []
keys = []

for schematic in lockSchematics:
    pattern = [0] * 5
    for row in schematic.split("|"):
        for i, ch in enumerate(row):
            if ch == "#":
                pattern[i] += 1
    if schematic.startswith("#####"):
        locks.append(pattern)
    else:
        keys.append(pattern)

pairs = 0
for lock in locks:
    for key in keys:
        if all([x + y <= 7 for x, y in zip(lock, key)]):
            pairs += 1
print(pairs)
