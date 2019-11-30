import subprocess
import time
import gc

#while True:
    #string='start'
    #print(string)    
    #smoke_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/smoke_sensor'])   
rain_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/rain_sensor'])
    #fire_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/fire_sensor'])
    #soil_moisture_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/soil_moisture'])
    #soil_moisture_output =int(soil_moisture_output)/1023*100
    #humidity_temp_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/humidity_sensor'])
    #while (str(humidity_temp_output)=="b'00.00|00.00'"):
        #print("error")
        #time.sleep(1)
        #humidity_temp_output=None
        #gc.collect()
        #humidity_temp_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/humidity_sensor'])
    #gps_output = subprocess.check_output(args=['/home/odroid/tensortest/Object_detection_file_old/serialport_read'])
    #gps_output = str(gps_output)[:-1]
    #time.sleep(1)
    #print(smoke_output, rain_output, soil_moisture_output, humidity_temp_output, gps_output)
print(rain_output)
    
    #humidity_temp_output=None
    #gc.collect()
time.sleep(10)
