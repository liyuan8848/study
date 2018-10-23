from __future__ import print_function
from struct import *
import sys
import traceback
import socket
import serial
import time

logfile = open("/data/var/log/sidband",'wa')

UDP_IP = "127.0.0.1"

UDP_PORT_TO_CPE = 11108

def send_udp(data):
    print(data, file=sys.stderr)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # print(data)
    sock.sendto(data, (UDP_IP, UDP_PORT_TO_CPE))
    #data, addr = sock.recvfrom(1024)
    #print("Recv >> "+data, file=sys.stderr)


ser= serial.Serial( \
    port='/dev/ttyS0', \
    baudrate=115200, \
    parity=serial.PARITY_NONE, \
    stopbits=serial.STOPBITS_ONE, \
    bytesize=serial.EIGHTBITS, \
    # timeout=0.5, \
    write_timeout=0.5 \
)
ser.close()
ser.open()
print(ser.is_open)
print("connected to: " + ser.portstr)



while True:
        # command = ser.read()
        command = ser.readline()
        #print(command)
        logfile.writelines()
        send_udp(command)
