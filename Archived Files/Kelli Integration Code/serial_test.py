import odroid_wiringpi as wiringpi

serial = wiringpi.serialOpen('/dev/ttyS1',115200)
wiringpi.serialPuts(serial, "hello")
wiringpi.serialClose(serial)

