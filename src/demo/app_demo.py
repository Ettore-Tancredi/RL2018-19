import tkinter as tk
from PIL import ImageTk, Image
import os

root = tk.Tk()

it_num = 0

path = "/home/luigi/source/repos/rescueline/runs/27-12-14_42/"

img = ImageTk.PhotoImage(Image.open(path+str(it_num) + ".png"))
panel = tk.Label(root, image=img)
panel.pack(side="bottom", fill="both", expand="yes")

is_eval = False

def getorigin(eventorigin):
    global path
    global it_num
    global is_eval
    if not(is_eval):
        is_eval = True
    else:
        it_num += 1
        is_eval = False
    if is_eval:
        img2 = ImageTk.PhotoImage(Image.open(path+str(it_num) + "_an.png"))
    else:
        img2 = ImageTk.PhotoImage(Image.open(path+str(it_num) + ".png"))
    panel.configure(image=img2)
    panel.image = img2
    

root.bind("<Button 1>", getorigin)
root.mainloop()

