import odroid_wiringpi as wpi
import time

serial = wpi.serialOpen('/dev/ttyUSB0', 115200)

while True:
	input_str='4000;1;21.3;1;11.7;1;0;1;0;1;0;1;13.7;1.23N;1.12W;1;2;0;0'
	wpi.serialPuts(serial, input_str)
	time.sleep(30)

wpi.serialClose(serial)
