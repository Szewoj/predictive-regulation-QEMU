import socket
import struct


HOST = '0.0.0.0'
PORT = 65433  

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
print("IP address:")
print(s.getsockname()[0])
print("Port:")
print(PORT)
s.close()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as GuiSocket:
    
    GuiSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    GuiSocket.bind((HOST, PORT))
    GuiSocket.listen()
    while True:
        GuiConnection, GuiAddress = GuiSocket.accept()
        with GuiConnection:
            print(GuiConnection)
            print(GuiAddress)
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

                    elif desc[0] == 5 and desc[1]:
                        y, = struct.unpack('d', data[2:10])
                        print("Then new output is: " + str(round(y, 2)))
                else:
                    break

