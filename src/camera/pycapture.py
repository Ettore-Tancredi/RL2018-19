import numpy as np
from picamera import PiCamera
from time import sleep


def pic(camera, path, it_num, width, height):
    camera.capture(path + str(it_num) + ".png")