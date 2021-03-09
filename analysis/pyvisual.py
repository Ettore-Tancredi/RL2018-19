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


neix = [0, 0,  0,  1, 1, 1, -1, -1, -1]
neiy = [0, 1, -1, -1, 0, 1,  0, -1,  1]

def highlight(mat, zc, H, W, green, tot_reg, b_x, b_y):
	im = mat
	pixelMap = im.load()

	img = Image.new( im.mode, im.size)
	pixelsNew = img.load()
	br = False
	wr = False
	gr = False
	it = True
	for i in range(H):
		for j in range(W):
			if j % 4 == 0:
				it = True
			else:
				it = False
			if zc[j][i] == 1:
				br = True
				wr = False
				gr = False
				pixelsNew[i,j] = (255,0,0,255)
			elif zc[j][i] > 1: 
				if green:
					if zc[j][i] > tot_reg:
						br = False
						wr = False
						gr = True
					else:
						wr = True
						br = False
						gr = False
						pixelsNew[i,j] = (255,255,0,255)
				else:
					wr = True
					br = False
					gr = False
					pixelsNew[i,j] = (255,255,0,255)
			else:  
				if it:
					if br and not(wr) and not(gr):
						pixelsNew[i,j] = (255,0,0,255)
					elif wr and not(br)and not(gr):
						pixelsNew[i,j] = (255,255,0,255)
					elif gr and not(br)and not(wr):
						pixelsNew[i,j] = (0,0,255,255)
				else:
					pixelsNew[i,j] = pixelMap[i,j]


	for k in range(0, 10):
		for m in range(0, 10):
			if int(b_y-5+k) < H and int(b_x-5+m) < W and int(b_y-5+k) >= 0 and int(b_x-5+m) >= 0 :
				pixelsNew[int(b_y-5+k),int(b_x-5+m)] = (0,255,255,255)
	for i in range(0, b_x):
		if int(b_y) < H and i < W and int(b_y) >= 0 and i >= 0:
			pixelsNew[int(b_y), i] = (0,255,255,255)
	for i in range(0, b_y):
		if i < H and int(b_x) < W and int(b_x) >= 0 and i >= 0:
			pixelsNew[i, int(b_x)] = (0,255,255,255)	

	img.show()
	im.show()

		




def draw(zc, H, W):
	#display the results of the tour. (Draws the borders of the regions it has found)
	window = Tk()
	canvas = Canvas(window, width=W+50, height=H+50, bg="#ffffff")
	canvas.pack()
	img = PhotoImage(width=W, height=H)
	canvas.create_image((W/2+20, H/2+20), image=img, state="normal")
	for i in range(H):
		for j in range(W):
			color = "#ffffff"
			if zc[j][i] == 1:
				color = '#000000'
			elif zc[j][i] == 2:
				color = '#00ffff'
			elif zc[j][i] == 3:
				color = '#ff0000'
			elif zc[j][i] == 4:
				color = '#ffff00'
			elif zc[j][i] == 5:
				color = '#009933'
			elif zc[j][i] == 6:
				color = '#ff00ff'
			elif zc[j][i] == 7:
					color = '#002699'

			img.put(color, (i,j))
			window.update()
	sleep(5)
	# mainloop()
	# window.destroy()



def pltmap(arr, H, W):
	x = range(W)
	y = range(H)
	X, Y = numpy.meshgrid(x, y)
	
	#transpose the matrix to plot correctly
	transp = [0] * H
	for i in range(H):
	    transp[i] = [0] * W
	for i in range(H):
	    for j in range(W):
	        transp[j][i] = (arr[i][j][0] + arr[i][j][1] + arr[i][j][2])/3

	Z = np.array(transp)
	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	ax.plot_surface(X, Y, Z)
	plt.show()
