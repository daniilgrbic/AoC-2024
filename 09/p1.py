#!/bin/python

import itertools

layout = map(int, input())
disk = []

for idx, length in enumerate(layout):
    if idx % 2 == 0:
        disk.extend([idx // 2] * length)
    else:
        disk.extend([None] * length)

left = 0
right = len(disk) - 1

while left < right:
    if disk[left] != None:
        left += 1
    elif disk[right] == None:
        right -= 1
    else:
        disk[left] = disk[right]
        disk[right] = None

disk = [(0 if bl == None else bl) for bl in disk]

checksum = sum([a * b for a, b in zip(disk, range(len(disk)))])
print(checksum)
