import os
import sys
import inspect
# you need this because sudo is messing with the python path on odroid
import subprocess
import time
import datetime
import gc


print('beginning script')

humidity_temp_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/humidity_sensor'])
while (str(humidity_temp_output)=="b'00.00|00.00'"):
    print("trying again")
    time.sleep(1)
    humidity_temp_output=None
    gc.collect()
    humidity_temp_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/humidity_sensor'])    
humidity_string = str(humidity_temp_output)[2:-1]
temp_output, humidity_output = humidity_string.split('|')       
print('temp done')     


smoke_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/smoke_sensor']) 
smoke_output = str(smoke_output)[2:-1]
print('smoke done')        
rain_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/rain_sensor'])
rain_output = str(rain_output)[2:-1]  
print('rain done')          
soil_moisture_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/soil_moisture'])        
soil_moisture_output = str(soil_moisture_output)[2:-1]
soil_moisture_output = int(soil_moisture_output)/1022*100
soil_moisture_output = str(soil_moisture_output) 
if (len(soil_moisture_output) >= 5):
    soil_moisture_output = soil_moisture_output[:-(len(soil_moisture_output)-5)]    
print('soil moisture done')         


gps_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/serialport_read'])
gps_output = str(gps_output)[2:-1]  
#gps_output = '33.3N|22.2W'        
gps_latitude, gps_longitude = gps_output.split('|')
if (gps_latitude[len(gps_latitude)-1] == 'N'):
    gps_latitude=gps_latitude[:-1]
    gps_latitude=int(gps_latitude)/100
else:
    gps_latitude=gps_latitude[:-1]
    gps_latitude=int(gps_latitude)/100*-1
gps_latitude=str(gps_latitude)        
if (gps_longitude[len(gps_longitude)-1] == 'E'):
    gps_longitude=gps_longitude[:-1]
    gps_latitude=int(gps_longitude)/100
else:
    gps_longitude=gps_longitude[:-1]
    gps_longitude=int(gps_longitude)/100*-1
gps_longitude=str(gps_longitude)            
print('gps done')

fire_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/fire_sensor'])   
fire_output = str(fire_output)[2:-4]         
print("fire done")  

from PIL import Image as im
import Object_Classification
import odroid_wiringpi as wpi
  
take_image = subprocess.run(['sudo', 'fswebcam', '-d', '/dev/video0', '-r', '840x480', 'image.jpg'])
time.sleep(1)
image_to_process = im.open('image.jpg')     
image_processing_output = Object_Classification.Object_Classification(image_to_process)
os.remove('image.jpg')

bears=str(image_processing_output[0])
deer=str(image_processing_output[1])
lynx=str(image_processing_output[2])
wolves=str(image_processing_output[3])

#currentDT=datetime.datetime.now()
#print(currentDT.strftime("%H:%M:%s"))

#print(smoke_output, rain_output, soil_moisture_output, humidity_output, temp_output, gps_output)

serial = wpi.serialOpen('/dev/ttyS1', 115200)

string_to_send = '4000'+';'+'1'+';'+temp_output+';'+'1'+';'+humidity_output+';'+'1'+';'+rain_output+';'+'1'+';'+smoke_output+';'+'1'+';'+fire_output+';'+'1'+';'+soil_moisture_output+';'+gps_latitude+';'+gps_longitude+';'+bears+';'+deer+';'+lynx+';'+wolves
#string_to_send='ahhhhhhhhhh'
print(str(string_to_send))

wpi.serialPuts(serial, string_to_send)
wpi.serialClose(serial)

humidity_temp_output=None
humidity_string=None
gc.collect()
time.sleep(300)


