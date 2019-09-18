from machine import UART
import time
#import json


u = UART(1)
while True:
    uart_data = u.read()
    if uart_data:
        time.sleep_ms(5)
        string=str(uart_data)
        n=4
        new_string=[string[i:i+n] for i in range(0, len(string), n)]
        msg_dict=dict()
        msg_dict.update({'device_id':new_string[0]})
        msg_dict.update({'temperature_id':new_string[1]})
        msg_dict.update({'temperature_reading':new_string[2]})
        msg_dict.update({'humidity_id':new_string[3]})
        msg_dict.update({'humidity_reading':new_string[4]})
        msg_dict.update({'rainfall_id':new_string[5]})
        msg_dict.update({'rainfall_reading':new_string[6]})
        msg_dict.update({'smoke_id':new_string[7]})
        msg_dict.update({'smoke_reading':new_string[8][-1:]})
        msg_dict.update({'fire_id':new_string[9]})
        msg_dict.update({'fire_reading':new_string[10][-1:]})
        msg_dict.update({'soil_moisture_id':new_string[11]})
        msg_dict.update({'soil_moisture_reading':new_string[12]})
        msg_dict.update({'GPS_latitude':new_string[13]})
        msg_dict.update({'GPS_longitude':new_string[14]})
        msg_dict.update({'image_bears':new_string[15]})
        msg_dict.update({'image_deer':new_string[16]})
        msg_dict.update({'image_lynx':new_string[17]})
        msg_dict.update({'image_wolves':new_string[18]})
        
        print(str(uart_data, 'utf8'), end='')
        print(msg_dict)
    time.sleep_ms(5)




