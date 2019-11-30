import odroid_wiringpi as wiringpi

serial = wiringpi.serialOpen('/dev/ttyS1',115200)
string_to_send="4000;1;23.7;1;45.4;1;0;1;0;1;0;1;99.9;11.3;-96.7;0;0;0;0"
wiringpi.serialPuts(serial, string_to_send)
wiringpi.serialClose(serial)

