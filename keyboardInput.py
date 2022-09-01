
import serial
import time
from pynput.keyboard import Key, Controller

ArduinoSerial = serial.Serial('COM8',9600)
keyboard = Controller()

while 1:
    data = str(ArduinoSerial.readline().decode('ascii'))
    (a,b,c) = data.split(":")
    (pos,acce,back) = (int(a),int(b),int(c))
    if acce==1:
        keyboard.press('w')
        keyboard.release('w')
    if back==1:
        keyboard.press('s')
        keyboard.release('s')
    if pos>0:
        keyboard.press('d')
        keyboard.release('d')
    elif pos<0:
        keyboard.press('a')
        keyboard.release('a')