import numpy.ctypeslib as ctl
import numpy as np
import ctypes
from PIL import Image
from numpy.random import randint
import numpy
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
#from mpl_toolkits.mplot3d import axes3d
#from matplotlib import cm
from tkinter import Tk, Canvas, PhotoImage, mainloop
from time import sleep
import random
from pyvisual_demo import *
import time
import sys
from math import sqrt

string = sys.argv[len(sys.argv)-1]


Cases = {-1 : "NO_LINE",
          0 : "STD_LINE",
          1 : "C_INTERSECTION",
          2 : "T_INTERSECTION",
          3 : "INTERUPT",
          4 : "GREEN_RIGHT",
          5 : "GREEN_LEFT",
          6 : "GREEN_BOTH"
}


H = 200
W = 200

#LOAD DLL
libname = 'imagelib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)
pyAnalyse = lib.load_image
pyAnalyse.argtypes = [np.ctypeslib.ndpointer(dtype=np.intc, ndim=3, flags='C_CONTIGUOUS')]
pyAnalyse.restype = np.ctypeslib.ndpointer(dtype=np.intc, shape=H*W+7)
pyLoad = lib.load_training_data

current_milli_time = lambda: int(round(time.time() * 1000))

pyLoad()

t0 = current_milli_time()

#LOAD IMAGE
mat = Image.open(string)
arr = np.array(mat, dtype=np.intc)
dim = arr.shape
H = dim[0]
W = dim[1]

instr = pyAnalyse(arr)

temp = instr
t1 = current_milli_time()

elapsed_time = t1 - t0
print(elapsed_time, " ms")


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


highlight(mat, zc, H, W, (Cases[instr[H*W]] == "GREEN_LEFT" or Cases[instr[H*W]] == "GREEN_RIGHT" or Cases[instr[H*W]] == "GREEN_BOTH"), instr[H*W+4] + instr[H*W+5], instr[H*W+1], instr[H*W+2])

f = open("tan.txt", "r")
f1 = f.readlines()
x = []
y = []
for t in f1:
    p = ""
    i = 0
    while t[i] != " ":
        p+= t[i]
        i += 1
    i+=1
    x.append(int(p))
    p = ""
    while i < len(t)-1:
        p+= t[i]
        i += 1
    y.append(int(p))


list1, list2 = (list(t) for t in zip(*sorted(zip(x, y))))

x_dist = abs(list1[0] - list1[len(list1)-1])
y_dist = abs(y[0] - y[len(y)-1])

rapp = y_dist/x_dist
figure(num=None, figsize=(3, 3*rapp), dpi=80, facecolor='w', edgecolor='k')
plt.plot(list1, list2, "bo")

# i = 0
# while i+7 < len(y):
#     y_list = []
#     x_list = []
#     if x[i] - x[i+7] != 0:
#         k = i
#         ang = (y[i]-y[i+7])/(x[i] - x[i+7])
#         i+=7
#         x_list.append(x[k])
#         y_list.append(y[k])
#         n_coord = (((x[i]-x[k])*ang + y[k]) - y[i])*(((x[i]-x[k])*ang + y[k]) - y[i])
#         while sqrt(n_coord + (x[i]-x[k])*(x[i]-x[k])) <= 50 and i < len(x)-1:
#             x_list.append(x[i])
#             y_list.append((x[i]-x[k])*ang + y[k])
#             xlist1, ylist2 = (list(t) for t in zip(*sorted(zip(x_list, y_list))))
#             plt.plot(xlist1, ylist2)
#             i+=1
#     else:
#         k = i
#         i+=7
#         x_list.append(x[k])
#         y_list.append(y[k])
#         while abs(x[i] - x[k]) <= 10 and i < len(x)-1:
#             x_list.append(x[k])
#             y_list.append(y[i])
#             xlist1, ylist2 = (list(t) for t in zip(*sorted(zip(x_list, y_list))))
#             plt.plot(xlist1, ylist2)
#             i+=1
#plt.plot([-10, -20, 0], s[10, 20, 30])


tan = 1000000

diff = 60
D_x = x[diff] - x[0]
D_y = y[diff] - y[0]

if D_x:
    tan = D_y / D_x

print("Slope:", tan)

x_list = []
y_list = []
for i in range(0, diff+30):
    if tan == 10000:
        y_list.append(i)
        x_list.append(x[0])
    else:
        y_list.append((x[i]-x[0])*tan)
        x_list.append(x[i])
xlist1, ylist2 = (list(t) for t in zip(*sorted(zip(x_list, y_list))))
plt.plot(xlist1, ylist2, "r")


plt.show()

#pltmap(arr, H, W)
#draw(zc, H, W)
