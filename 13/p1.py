#!/bin/python

import re
import sys

inputText =  [line for line in sys.stdin]
inputText = "|".join(inputText).replace("\n","")
machineInfo = inputText.split("||")

totalPrice = 0

for i, machine in enumerate(machineInfo):

    print(f"Clawing {i+1}/{len(machineInfo)}:", machine)

    x1, y1, x2, y2, x, y = map(int, re.findall("\\d+", machine))
    minMachinePrice = float("inf")

    for i in range(100):
        for j in range(100):
            if x1*i + x2*j == x and y1*i + y2*j == y:
                price = i * 3 + j
                minMachinePrice = min(minMachinePrice, price)

    if minMachinePrice != float("inf"):
        totalPrice += minMachinePrice

print(totalPrice)
