from umqtt.simple import MQTTClient
import json
import time
from machine import UART

u = UART(1)
while True:
    uart_data = u.read()
    if uart_data:
        string=str(uart_data)
        print(string)
        msg_dict=dict()
        string=string[2:-1]
        new_string=string.split(';')
        print(new_string)
        msg_dict.update({'device_id':int(new_string[0])})
        msg_dict.update({'temperature_id':new_string[1]})
        msg_dict.update({'temperature_reading':new_string[2]})
        msg_dict.update({'humidity_id':new_string[3]})
        msg_dict.update({'humidity_reading':new_string[4]})
        msg_dict.update({'rainfall_id':new_string[5]})
        msg_dict.update({'rainfall_reading':int(new_string[6])})
        msg_dict.update({'smoke_id':new_string[7]})
        msg_dict.update({'smoke_reading':int(new_string[8])})
        msg_dict.update({'fire_id':new_string[9]})
        msg_dict.update({'fire_reading':int(new_string[10])})
        msg_dict.update({'soil_moisture_id':new_string[11]})
        msg_dict.update({'soil_moisture_reading':new_string[12]})
        msg_dict.update({'GPS_latitude':new_string[13]})
        msg_dict.update({'GPS_longitude':new_string[14]})
        msg_dict.update({'image_bears':int(new_string[15])})
        msg_dict.update({'image_deer':int(new_string[16])})
        msg_dict.update({'image_lynx':int(new_string[17])})
        msg_dict.update({'image_wolves':int(new_string[18])})
        json_dict_one = json.dumps(msg_dict)
        print(json_dict_one)
        if __name__ == '__main__':
            time.sleep(20)
            for i in range(0,10000):

                try:
                    mqtt = MQTTClient("digitest", "test.mosquitto.org", port=1883)  # Create instance of client with client ID “digitest”
                    #mqtt = MQTTClient("digitest", "broker.hivemq.com", port=1883)
                    mqtt.connect()
                    print("connect")
                    mqtt.publish('digitest/test1', str(json_dict_one))
                    mqtt.disconnect()
                except Exception as e:
                    #print(e)
                    continue
                print("made it")
                break
            time.sleep(60)
    time.sleep_ms(5)

