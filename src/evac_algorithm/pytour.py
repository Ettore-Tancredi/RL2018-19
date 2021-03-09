import numpy.ctypeslib as ctl
import ctypes
import numpy as np
import time

libname = 'tourlib.so'
libdir = './'
lib=ctl.load_library(libname, libdir)

py_analyse = lib.load_points
py_analyse.argtypes = [np.ctypeslib.ndpointer(dtype=np.intc, ndim=1, flags='C_CONTIGUOUS'), ctypes.c_int]
py_analyse.restype = np.ctypeslib.ndpointer(dtype=np.intc, shape=12)

locations = [90, 10, 20, 30, 30, 20, 10, 100, 10, 10, 50, 70, 90, 100, 20, 2, 90, 12, 34,  120, 45, 60, 72, 8]

t0 = time.time()

path = py_analyse(np.array(locations, dtype=np.intc), int(len(locations)))

t1 = time.time()

elapsed_time = t1 - t0
print(elapsed_time, " s")

path = [i for i in path if i != -1]


print(path)
