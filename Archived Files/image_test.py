import subprocess
from time import sleep
import os
from PIL import Image


def image_delete (img):
	sleep(100)
	os.remove('image.jpg')
	return 0	


proc=subprocess.Popen("sudo fswebcam -d /dev/video0 -r 840x480 image.jpg", shell=True)
proc.wait()
sleep(1)
img=Image.open('image.jpg')
image_delete(img)
