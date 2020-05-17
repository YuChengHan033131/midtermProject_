import serial
import struct #bytes and float convert
import time #to sleep

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
formatter = lambda x: "%6.2f" % x

while 1:
    key=s.readline()
    if "Hopes and Dreams" in key.decode():
        with open("Hopes_and_Dreams.txt",'r+') as file:
            print("loading Hopes_and_Dreams")
            for line in file:
                s.write(bytes(line, 'UTF-8'))
                time.sleep(.1)
        time.sleep(1)
    if "Your Best Friend" in key.decode():
        with open("Flowey_Your_Best_Friend.txt",'r+') as file:
            print("loading Flowey_Your_Best_Friend")
            for line in file:
                s.write(bytes(line, 'UTF-8'))
                time.sleep(.1)
        time.sleep(1)
    if "song3" in key.decode():
        with open("song3.txt",'r+') as file:
            print("loading song3")
            for line in file:
                s.write(bytes(line, 'UTF-8'))
                time.sleep(.1)
        time.sleep(1)
    else:
        print("song doesn't exist")
s.close()
