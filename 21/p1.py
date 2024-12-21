#!/bin/python

import sys
from common import *

result = 0

for code in sys.stdin:
    code = code.strip()
    ways = minimal_sequence_length(NUM_PAD, code, 3)
    result += ways * int(code if code[-1] != 'A' else code[:-1])

print("Part 1:", result)
