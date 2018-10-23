import serial
import time

ser= serial.Serial( \
    port='/dev/ttyUSB0', \
    baudrate=9600, \
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
        print(command)
