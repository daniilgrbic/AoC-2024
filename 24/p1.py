#!/bin/python

import sys
from operator import and_, or_, xor

values = {
    # wire -> value | (gate, input_1, input_2)
}

wires = set()

# read system input
while (line := sys.stdin.readline().strip()) != "":
    wire, value = line.split(": ")
    values[wire] = int(value)

# read gates and connections 
while (line := sys.stdin.readline().strip()) != "":
    input_1, gate, input_2, _, wire = line.split()
    values[wire] = (gate, input_1, input_2)
    wires.add(wire)

def evaluate(values, wire) -> int:
    if type(values[wire]) == int:
        return values[wire]
    gate, input_1, input_2 = values[wire]
    input_1_value = evaluate(values, input_1)
    input_2_value = evaluate(values, input_2)
    match gate:
        case "AND": value = input_1_value & input_2_value 
        case "OR":  value = input_1_value | input_2_value 
        case "XOR": value = input_1_value ^ input_2_value 
    values[wire] = value
    return value

while wires:
    wire = wires.pop()
    values[wire] = evaluate(values, wire)

z_values = [(wire, val) for wire, val in values.items() if wire.startswith("z")]
z_values.sort()

result = 0
for i, (wire, bit) in enumerate(z_values):
    result += bit * pow(2, i)
print(result)
