#!/bin/python

import re
import sys

program = [line for line in sys.stdin]
program = "|".join(program)

instructions = re.findall("mul\\(\\d+,\\d+\\)", program)
print(instructions)

def evaluate(instruction):
    a, b = map(int, re.findall("\\d+", instruction))
    return a * b 

result = sum(evaluate(i) for i in instructions) 
print(result)
