#!/usr/bin/env python3

import StepResponse as SR
from DMC import DMC
from RepeatedTimer import RepeatedTimer
from time import sleep

def cyclic_routine(dmc):
    # TODO get simulation values
    y = 0.0
    z = 0.0
    u = dmc.calculate_U(y, z)
    print(u)
    # TODO send response with u


def main():
    regulator = DMC()
    regulator.init_regulator(100, 15, 8)

    rt = RepeatedTimer(0.5, cyclic_routine, regulator)

    try:
        while(True):
            sleep(1)
    finally:
        rt.stop()

    
    

if __name__ == '__main__':
    main()

