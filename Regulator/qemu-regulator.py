#!/usr/bin/env python3

import StepResponse as SR
from DMC import DMC
from RepeatedTimer import RepeatedTimer
from time import sleep
import socket
import struct

HOST = '0.0.0.0'
PORT = 65433
PORT2 = 65434

def cyclic_routine(dmc, connection):
    connection.send(struct.pack("BB", 4, 0))
    data = connection.recv(20)
    if len(data) > 2:
        d = struct.unpack('BB', data[:2])
    if d[0] == 1 and d[1] == 16:
        y, = struct.unpack('d', data[2:10])
        z, = struct.unpack('d', data[10:18])
    u = dmc.calculate_U(y, z)
    print(u)
    connection.send(struct.pack("BBd", 5, 8, u))

def main():
    regulator = DMC()
    regulator.init_regulator(100, 15, 8)

    GuiSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    GuiSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    GuiSocket.bind((HOST, PORT))
    GuiSocket.listen()
    GuiConnection, GuiAddress = GuiSocket.accept()
    print(GuiConnection)
    print(GuiAddress)

    ObjSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ObjSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    ObjSocket.bind((HOST, PORT2))
    ObjSocket.listen()
    ObjConnection, ObjAddress = ObjSocket.accept()

    print(ObjConnection)
    print(ObjAddress)

    rt = RepeatedTimer(0.5, cyclic_routine, regulator, ObjConnection)

    try:
        while True:
            with GuiConnection:
                dataACK = GuiConnection.recv(2)
                #if len(dataACK) < 2:
                d = struct.unpack('BB', dataACK[:2])
                while True:
                    if d[0] == 1 and d[1] ==0:
                        data = GuiConnection.recv(20)

                        if not data:
                            break
                        desc = struct.unpack('BB', data[:2])

                        if desc[0] == 6 and desc[1] == 20:
                            y, = struct.unpack('d', data[2:10])
                            N, Nu = struct.unpack('BB', data[10:12])
                            lbda, = struct.unpack('d', data[12:20])
                            print("Then new parametrs are: " + str(round(y, 2)) + " " + str(N) + " " + str(Nu) + " " + str(round(lbda,2)))
                            regulator.init_regulator(N, Nu, lbda)

                        elif desc[0] == 5 and desc[1]:
                            y, = struct.unpack('d', data[2:10])
                            print("Then new output is: " + str(round(y, 2)))
                            regulator.set_yzad(y)
                    else:
                        break
    finally:
        rt.stop()

    
    

if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    print("IP address:")
    print(s.getsockname()[0])
    print("Port GUI:")
    print(PORT)
    print("Port DMC:")
    print(PORT2)
    s.close()

    main()

