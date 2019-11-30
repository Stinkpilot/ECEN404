import odroid_wiringpi as wpi
import time

wpi.wiringPiSetup()
wpi.pinMode(10,1)

while True:
    wpi.digitalWrite(10,1)
    time.sleep(30)
