import numpy.ctypeslib as ctl
import numpy as np
import ctypes
from PIL import Image
from numpy.random import randint
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import numpy

libname = 'testlib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)

pyPrint = lib.printArr
pyPrint.argtypes = [np.ctypeslib.ndpointer(dtype=np.intc, ndim=3, flags='C_CONTIGUOUS'), ctypes.c_int, ctypes.c_int]
pyPrint.restype = np.ctypeslib.ndpointer(dtype=np.intc, shape=160000)

mat = Image.open("/home/luigi/repos/rescueline/src/figures/frames/frame6.png")
arr = np.array(mat, dtype=np.intc)
print(arr.ndim)
H = 400
W = 400
# arr2 = [0] * H
# for i in range(H):
#     arr2[i] = [0] * W
# for i in range(H):
#     for j in range(W):
#             arr2[i][j] = [0] * 3
#
#
# for i in range(H):
#     for j in range(W):
#         arr2[i][j][0] = arr1[i][j][0]
#         arr2[i][j][1] = arr1[i][j][1]
#         arr2[i][j][2] = arr1[i][j][2]

# arr = np.array(arr2, dtype=np.intc)


# arr3 = randint(200, size=(H, W, 3))
# arr = np.array(arr3, dtype=np.intc)
# z = [0] * H
# for i in range(H):
#     z[i] = [0] * W
# for i in range(0, H):
#     for j in range(0, W):
#         z[j][i] = arr[i][j]

print("AAAAAAAAAA")

# arr1 = np.array(z)

ZC = pyPrint(arr, np.intc(H), np.intc(W))

print("BBBBBBBBBBBBb")

x = range(W)
y = range(H)

z_val = [0] * H
for i in range(H):
    z_val[i] = [0] * W
for i in range(0, H):
    for j in range(0, W):
        val = int((arr[i][j][0] + arr[i][j][1] + arr[i][j][2]) / 3)
        # z_val[j][i] = val;
        rem = val%10
        if rem >= 5:
            z_val[j][i] = val + (10 - rem)
        else:
            z_val[j][i] = val - rem

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

Z = np.matrix(z_val)
X, Y = numpy.meshgrid(x, y)

ax.plot_wireframe(X, Y, Z)
plt.show()

fig1 = plt.figure()
ax1 = fig1.add_subplot(111, projection='3d')

z_valc = [0] * H
for i in range(H):
    z_valc[i] = [0] * W
for i in range(0,H*W):
    z_valc[int(i/W)][(i%W)] = ZC[i]
print(z_valc[0][0])

ZCn = np.matrix(z_valc)

ax1.plot_wireframe(X, Y, ZCn)
plt.show()
