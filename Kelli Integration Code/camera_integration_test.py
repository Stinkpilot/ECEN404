from PIL import Image as im
import Object_Classification
import subprocess
import os
import time
import gc


take_image = subprocess.run(['sudo', 'fswebcam', '-d', '/dev/video0', '-r', '840x480', 'image.jpg'])   
time.sleep(10)
image_to_process = im.open('image.jpg')
animals=Object_Classification.Object_Classification(image_to_process)
os.remove('image.jpg')
   
print(animals) 
    
time.sleep(10)
