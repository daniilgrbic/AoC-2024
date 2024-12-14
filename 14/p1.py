#!/bin/python

import sys
import re

dims, *robots = [line for line in sys.stdin]

width, height = map(int, dims.split())
hw, hh = width // 2, height // 2 
time = 100

quads = [[0, 0], [0, 0]]

for robot in robots:

    px, py, vx, vy = map(int, re.findall("\\-*\\d+", robot))

    x = (px + time * vx) % width
    y = (py + time * vy) % height

    if x == hw or y == hh:
        continue

    quads[x // (hw+1)][y // (hh+1)] += 1

print(quads)

print(quads[0][0] * quads[1][0] * quads[0][1] * quads[1][1])
