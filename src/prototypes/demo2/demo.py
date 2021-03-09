import numpy.ctypeslib as ctl
import numpy as np
import ctypes
from PIL import Image
from numpy.random import randint
import numpy
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
from tkinter import Tk, Canvas, PhotoImage, mainloop
from time import sleep
import random
from pyvisual_demo import *
import time
import sys

string = sys.argv[len(sys.argv)-1]

Cases = {-1 : "NO_LINE",
          0 : "STD_LINE",
          1 : "C_INTERSECTION",
          2 : "T_INTERSECTION",
          3 : "INTERUPT",
          4 : "GREEN"
}

Green_Cases = { 0 : "G_LEFT",
                1 : "G_RIGHT",
                2 : "G_BOTH"
}



#LOAD DLL
libname = 'imagelib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)
pyAnalyse = lib.load_image
pyAnalyse.argtypes = [np.ctypeslib.ndpointer(dtype=np.intc, ndim=3, flags='C_CONTIGUOUS'), ctypes.c_int, ctypes.c_int]
pyAnalyse.restype = np.ctypeslib.ndpointer(dtype=np.intc, shape=160006)

current_milli_time = lambda: int(round(time.time() * 1000))

t0 = current_milli_time()

#LOAD IMAGE


mat = Image.open(string)
arr = np.array(mat, dtype=np.intc)
dim = arr.shape
H = dim[0]
W = dim[1]

instr = pyAnalyse(arr, H, W)
temp = instr
t1 = current_milli_time()

elapsed_time = t1 - t0
print(elapsed_time, " ms")

if Cases[instr[H*W]] == "GREEN":
    print(Green_Cases[instr[H*W+3]])
else:
    print(Cases[instr[H*W]])

print("Barycentre: (", instr[H*W+1], ",", instr[H*W+2], ")" )
print("White regions:", instr[H*W+4])
print("Black regions:", instr[H*W+5])


#convert array to matrix
zc = [0] * H
for i in range(H):
    zc[i] = [0] * W
for i in range(0,H*W):
    zc[int(i/W)][(i%W)] = instr[i]


highlight(mat, zc, H, W, Cases[instr[H*W]] == "GREEN", instr[H*W+4] + instr[H*W+5], instr[H*W+1], instr[H*W+2])
#pltmap(arr, H, W)
#draw(zc, H, W)

