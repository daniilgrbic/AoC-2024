#!/bin/python

import re
import sys

inputText =  [line for line in sys.stdin]
inputText = "|".join(inputText).replace("\n","")
machineInfo = inputText.split("||")

totalPrice = 0
error = 10000000000000

for i, machine in enumerate(machineInfo):

    print(f"Clawing {i+1}/{len(machineInfo)}:", machine)

    x1, y1, x2, y2, x, y = map(int, re.findall("\\d+", machine))
    x += error
    y += error

    determinant = x1*y2 - x2*y1
    assert determinant != 0

    if (y2*x - x2*y) % determinant != 0:
        print("   No integer solution.")
        continue
    A = (y2*x - x2*y) // determinant

    if (x - x1*A) % x2 != 0:
        print("   No integer solution.")
        continue
    B = (x - x1*A) // x2

    print(f"   {A}*3 + {B}*1 = {A*3+B}")

    totalPrice += A * 3 + B

print(totalPrice)
