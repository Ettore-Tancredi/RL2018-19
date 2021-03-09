import numpy as np
from picamera import PiCamera
from time import sleep
from sys import argv


delay = argv[len(argv)-2]
filename = argv[len(argv)-1]

width = 400
height = 400

camera = PiCamera()
camera.resolution = (width, height)
camera.start_preview()
sleep(int(delay))
camera.capture('/home/pi/repos/rescueline/runs/' + filename + '.png')
camera.stop_preview()
