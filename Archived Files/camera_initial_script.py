import subprocess
from time import sleep
import os
import image_processing_model
from PIL import image

def camera_script():
    proc=subprocess.Popen("sudo fswebcam -d /dev/video0 -r 840x480 image.jpg", shell=True)
    proc.wait()
    sleep(1)
    img=Image.open('image.jpg')
    bears,deer,lynx,wolves=image_processing_model.func(img)
    sleep(1)
    os.remove('image.jpg')
    return(bears,deer,lynx,wolves)