import subprocess
import time
import os 
from PIL import Image
import Object_detection_image

while True:
  smoke_output = subprocess.check_output(args=['./smoke_sensor'])
  rain_output = subprocess.check_output(args=['./rain_sensor'])
  soil_moisture_output = subprocess.check_output(args=['./soil_moisture']
  humidity_temp_output = subprocess.check_output(args=['./humidity'])
  humidity_output=
  temp_output=
  fire_output = subprocess.check_output(args=['./fire_sensor']
  
  gps_output = subprocess.check_output(args=['./gps']
  gps_output = str(gps_output)
  
  gps_latitude, gps_longitude = gps_output[:8], gps_output[8:]
  
  take_image = subprocess.Popen("sudo fswebcam -d /dev/video0 -r 840x480 image.jpg")
  take_image.wait()
  time.sleep(1)
  image_to_process = Image.open('image.jpg')
  image_processing_output = Object_detection_image(image_to_process)    
  os.remove('image.jpg')

  bears=image_processing_output[0]
  deer=image_processing_output[1]
  lynx=image_processing_output[2]
  wolves=image_processing_output[3]
        
  string_to_send = '4000'+';'+'1'+';'+str(temp_output)+';'+'1'+';'+str(humidity_output)+';'+'1'+';'+str(rain_output)[2:-1]+';'+'1'+';'+str(smoke_output)[2:-1]+';'+'1'+';'+str(fire_output)+';'+'1'+';'+str(soil_moisture_output)[2:-1]+';'+str(gps_latitude)+';'+gps_longitude+';'+gps_latitude+';'+str(bears)+';'+str(deer)+';'+str(lynx)+';'+str(wolves)

  print(str(string_to_send))
  
  file_object=open("sending_file.txt","w")   
  file_object.write(string_to_send)
  file_object.close()   
  subprocess.call('cat file_object > /dev/ttyS1')
  time.sleep(300)
