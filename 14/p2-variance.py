#!/bin/python

import sys
import re
import pygame as pg
import numpy as np

dims, *robots = [line for line in sys.stdin]
width, height = map(int, dims.split())

threshold = 500

for time in range(10000):

    print("Time:", time)

    xs, ys = [], []

    for robot in robots:

        px, py, vx, vy = map(int, re.findall("\\-*\\d+", robot))

        x = (px + time * vx) % width
        y = (py + time * vy) % height

        xs.append(x)
        ys.append(y)

    xvar = np.var(xs)
    yvar = np.var(ys)

    if xvar < threshold or yvar < threshold:
        frame = pg.Surface((width, height))
        for x, y in zip(xs, ys):
            frame.set_at((x, y), pg.Color("white"))
        pg.image.save(frame, f"frames-var/{time:04d}.png")
