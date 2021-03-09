import ctypes
from PIL import Image
import numpy
import numpy.ctypeslib as ctl
import numpy as np
from time import sleep
import random
import os
from subprocess import call
import time
from picamera import PiCamera
from math import sqrt

from pylog import Log
from usb_comm import USB
from line_cases import Cases
from pycapture import pic
from pyvisual_demo import *

H = 200
W = 200
camera = PiCamera()
camera.resolution = (W, H)
    
Cases1 = {-1 : "NO_LINE",
          0 : "STD_LINE",
          1 : "C_INTERSECTION",
          2 : "T_INTERSECTION",
          3 : "INTERUPT",
          4 : "GREEN_RIGHT",
          5 : "GREEN_LEFT",
          6 : "GREEN_BOTH"
}

def correction(x, y):
  global H, W
  y = H/2 - y
  x = x - W/2
  E = sqrt(x*x + y*y)
  return E


#LOAD DLLs
libname = 'imagelib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)
pyAnalyse = lib.load_image
pyAnalyse.argtypes = [np.ctypeslib.ndpointer(dtype=np.intc, ndim=3, flags='C_CONTIGUOUS')]
pyAnalyse.restype = np.ctypeslib.ndpointer(dtype=np.intc, shape=(H*W+400))
pyLoad = lib.load_training_data
run_id = "5-3-15_19/" #! + month_day_min 
path = "/home/pi/repos/rescueline/runs/" 
#os.mkdir(path + run_id)
#log = Log(path, run_id) 

#INITIALIZE SERIAL COMM
slave = USB(9600, "/dev/ttyUSB0")

'''
over = False
while not(over):
   slave.write(999) #! catch any exception (write to log)
   res = slave.read() #! catch any exception (write to log)
   if res == 888:
    #log.write("Serial comm started succesfully\n")
     print("Comm succeded")
     slave.write(1000)
     over = True
   else :
     #log.write("Unable to start serial comm:\n")
     #log.write("\tLog returned ")
     #log.write(res)
     #sleep(0.1)
     print("Comm failed")
'''

lastRoom = False
it_num = 47
delay = 0.1 #! temp value

current_milli_time = lambda: int(round(time.time() * 1000))

pyLoad()

while(not(lastRoom)):
    t0 = current_milli_time()

    pic(camera, path + run_id, it_num, H, W)
    mat = Image.open(path + run_id + str(it_num) + ".png")
    arr = np.array(mat, dtype=np.intc)
    dim = arr.shape

    instr = pyAnalyse(arr)

    t1 = current_milli_time()

    elapsed_time = t1 - t0
    print(elapsed_time, " ms")

    print(Cases1[instr[H*W]])
    
    print("Barycentre: (", instr[H*W+1], ",", instr[H*W+2], ")" )
    print("White regions:", instr[H*W+4])
    print("Black regions:", instr[H*W+5])
    print("Error", correction(instr[H*W+2], instr[H*W+1]))
    
    slave.write_char("s")
    if (instr[H*W+6] == 4): #allfour borders are black -> error!
        slave.write_char("C")      #temp
    if (Cases1[instr[H*W]] == "STD_LINE"):
        # slave.write_char("S")
        # slave.write(instr[H*W+2])
        # slave.write(instr[H*W+1])    
        tan = 1000000
        diff = 60
        D_x = instr[H*W+6+100] - instr[H*W+6+100]
        D_y = instr[H*W+6+101] - instr[H*W+6]

        if D_x:
            tan = D_y / D_x
        slave.write_char("S")
        slave.write(D_x)
        slave.write(D_y)    
    elif (Cases1[instr[H*W]] == "C_INTERSECTION"):
        slave.write_char("C")
    elif (Cases1[instr[H*W]] == "T_INTERSECTION"):
        slave.write_char("T")
    elif (Cases1[instr[H*W]] == "GREEN_BOTH"):
        slave.write("B")
    elif (Cases1[instr[H*W]] == "GREEN_RIGHT"):
        slave.write("R")
    elif (Cases1[instr[H*W]] == "GREEN_LEFT"):
        slave.write("L")

    zc = [0] * H
    for i in range(H):
        zc[i] = [0] * W
    for i in range(0,H*W):
        zc[int(i/W)][(i%W)] = instr[i]

    highlight(it_num, mat, zc, H, W, (Cases1[instr[H*W]] == "GREEN_LEFT" or Cases1[instr[H*W]] == "GREEN_RIGHT" or Cases1[instr[H*W]] == "GREEN_BOTH"), instr[H*W+4] + instr[H*W+5], instr[H*W+1], instr[H*W+2])
    show_image(it_num, path)
    
    slave.write_char("e")
    sleep(delay)

    it_num = it_num + 1
    lastRoom = (instr[H*W] == Cases.SILVER)

#warn arduino that the room has been found


#...




