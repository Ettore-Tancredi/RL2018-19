from tkinter import *
from PIL import ImageTk, Image
import os
import numpy as np


select = 0

x_2 = 0
y_2 = 0

def getorigin(eventorigin):
    x_1 = eventorigin.x
    y_1 = eventorigin.y
    global select
    if (select == 0):
        print(arr[x_1, y_1])
    if (select == 1):
        global x_2
        global y_2
        if (x_2 == 0):
            x_2 = x_1
            y_2 = y_1
        else:
            printArea(x_1, x_2, y_1, y_2)
            x_2 = 0
            y_2 = 0


def printArea(x2, x1, y2, y1):
    R = 0
    B = 0
    G = 0
    for i in range (y1, y2+1):
        for j in range(x1, x2+1):
            R = R + arr[i][j][0]
            B = B + arr[i][j][1]
            G = G + arr[i][j][2]
    R = int(R/((x2-x1)*(y2-y1)))
    G = int(G/((x2-x1)*(y2-y1)))
    B = int(B/((x2-x1)*(y2-y1)))
    print(R, G, B)



def selectArea():
    global select
    if (select == 0):
        select = 1
        print("area selezionata")
    else:
        select = 0
        print("area deselezionata")


mat = Image.open("/home/luigi/repos/rescueline/src/figures/frames/frame6.png")

root = Tk()
frame = Frame(root, width=800, height=600)
frame.pack()
img = ImageTk.PhotoImage(mat)
panel = Label(root, image = img)
arr = np.array(mat)
panel.place(x=0, y=0)
button = Button(root, text="AREA", command=selectArea)
button.place(x=500, y=200)

root.bind("<Button 1>", getorigin)

root.mainloop()
