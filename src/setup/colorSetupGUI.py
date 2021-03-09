from drawings import Drawings
from PIL import Image, ImageTk
import tkinter as tk
from colori2 import Filtro

path = "C:/Users/UTENTE/Documents/OII/colori/immagini/frame6.png"

root = tk.Tk()

canvas = tk.Canvas(root, width = 400, height = 400)
canvas.pack()

img = Image.open(path)
img = img.resize((400, 400))
px = img.load()
img_copy = img.copy()

'''for i in range(0, 4):
    myFiltro = Filtro(10, img_copy)
    img_copy = myFiltro.filtra()'''

px_copy = img_copy.load()

w = Drawings(img_copy, k = 15, k2 = 10)    # k = 15    k2 = 50      per riconoscimento linea
temp = ImageTk.PhotoImage(image = img_copy)
canvas.create_image(0, 0, anchor = tk.NW, image = temp)

#
#   Definitions
#
#
#

def isInside(c):
    if c[0] < 0 or c[0] >= img_copy.width or c[1] < 0 or c[1] >= img_copy.height:
        return False
    else:
        return True

def averageColor(event):
    c = 0
    media = (0, 0, 0)

    for y in range(-3, 4):
        for x in range(-3, 4):
            if isInside((event.x + x, event.y + y)):
                media = (media[0] + px_copy[event.x + x, event.y + y][0], media[1] + px_copy[event.x + x, event.y + y][1], media[2] + px_copy[event.x + x, event.y + y][2])
                c = c + 1

    return (media[0] / c, media[1] / c, media[2] / c)


def display(event):
    w.k = int(input("Immettere il valore di k:  "))
    w.k2 = int(input("Immettere il valore di k2:  "))
    #w.color = px[event.x, event.y]
    w.color = averageColor(event)

    w.draw().show()


#
#
#   End of definitions
#
#



root.bind('<Button-1>', display)
root.mainloop()