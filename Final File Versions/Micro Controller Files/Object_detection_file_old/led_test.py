


import odroid_wiringpi as wpi
import time

wpi.wiringPiSetup()
wpi.pinMode(0,1)

while True:
    wpi.digitalWrite(0,1)
    time.sleep(5)
    wpi.digitalWrite(0,0)
    time.sleep(2)
