# import picamera
# import picamera.array
import numpy.ctypeslib as ctl
import ctypes
import numpy
from time import sleep
from PIL import Image
import numpy as np

libname = 'imagelib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)


mat = Image.open("/home/luigi/repos/rescueline/src/figures/frames/frame7.png")
arr = np.array(mat)

W = 400
H = 400
# camera = picamera.PiCamera()
# camera.resolution = (W, H)
# output = picamera.array.PiRGBArray(camera)
# camera.start_preview()
# sleep(10)
# camera.capture(output, 'rgb')
# camera.capture("/home/pi/Desktop/img.jpg")
# camera.stop_preview()
# print(output.array[0][0])

py_analyse = lib.load_image
py_analyse.argtypes = [ctypes.c_int * (H * W * 3)]


A = ctypes.c_int * (H * W * 3)
ii = A()

it = 0;
for i in range(0, W):
    for j in range(0, H):
        for k in range(0, 3):
            # ii[it] = output.array[j][i][k]
            ii[it] = arr[j][i][k]
            it = it + 1

print("yeeee")

py_analyse(ii)
