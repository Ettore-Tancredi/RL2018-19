import numpy as np
from PIL import Image
import sys
from graph_functions import *


string = sys.argv[len(sys.argv)-2]
mat = Image.open(string)
arr = np.array(mat)

dim = arr.shape
H = dim[0]
W = dim[1]

for i in sys.argv:
    if i == "-card":
        card(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-map":
        graph_map(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-wir":
        graph_wir(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-mapG":
        graph_mapG(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-mapR":
        graph_mapR(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-mapB":
        graph_mapB(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-wirG":
        graph_wirG(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-diffR":
        graph_diffR(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-diffB":
        graph_diffB(arr, sys.argv[len(sys.argv)-1], H, W)
    if i == "-prc":
        graph_prc(arr, sys.argv[len(sys.argv)-1], H, W)
