import serial
import struct #bytes and float convert
import time #to sleep

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
formatter = lambda x: "%6.2f" % x

with open("Hopes_and_Dreams.txt",'r+') as file:
            print("loading Hopes_and_Dreams")
            for line in file:
                s.write(bytes(line, 'UTF-8'))
                time.sleep(.1)
