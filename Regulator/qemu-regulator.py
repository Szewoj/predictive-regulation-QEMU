#!/usr/bin/env python3

import StepResponse as SR
from DMC import DMC

if __name__ == '__main__':
    print("Hello World!")
    print(SR.Su[10])

    regulator = DMC()
    regulator.init_regulator(100, 15, 8)

    print(regulator._ke)

