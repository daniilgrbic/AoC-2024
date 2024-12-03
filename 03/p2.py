#!/bin/python

import re
import sys

program = [line for line in sys.stdin]
program = "|".join(program)

instructions = re.findall(
    "(mul\\(\\d+,\\d+\\)|don't\\(\\)|do\\(\\))", program)
print(instructions)

def evaluate(instruction):
    a, b = map(int, re.findall("\\d+", instruction))
    return a * b 

result = 0
mul_on = True
for instruction in instructions:
    match instruction:
        case "do()":
            mul_on = True
        case "don't()":
            mul_on = False
        case _ if mul_on:
            result += evaluate(instruction)

print(result)
