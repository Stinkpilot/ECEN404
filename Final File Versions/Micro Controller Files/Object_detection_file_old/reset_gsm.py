import odroid_wiringpi as wpi
import time

wpi.wiringPiSetup()
wpi.pinMode(4,1)

wpi.digitalWrite(4,1)
time.sleep(1)
wpi.digitalWrite(4,0)
time.sleep(1)
wpi.digitalWrite(4,1)
time.sleep(1)
