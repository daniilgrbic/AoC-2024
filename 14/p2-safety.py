#!/bin/python

import sys
import re
import pygame as pg

dims, *robots = [line for line in sys.stdin]

width, height = map(int, dims.split())
hw, hh = width // 2, height // 2 

threshold = ((len(robots) // 4) ** 4 )* 0.7

for time in range(10000):

    print("Time:", time)

    xs, ys = [], []
    quads = [[0, 0], [0, 0]]

    for robot in robots:

        px, py, vx, vy = map(int, re.findall("\\-*\\d+", robot))

        x = (px + time * vx) % width
        y = (py + time * vy) % height

        xs.append(x)
        ys.append(y)

        if x == hw or y == hh:
            continue

        quads[x // (hw+1)][y // (hh+1)] += 1
    
    safety = quads[0][0] * quads[1][0] * quads[0][1] * quads[1][1]
    if safety < threshold:
        frame = pg.Surface((width, height))
        for x, y in zip(xs, ys):
            frame.set_at((x, y), pg.Color("white"))
        pg.image.save(frame, f"frames-safety/{time:04d}.png")
