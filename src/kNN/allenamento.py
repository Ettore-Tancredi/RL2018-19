from tkinter import*
from PIL import Image, ImageTk
from os import sys


photo_path = sys.argv[len(sys.argv)-1]

root = Tk()
photo = Image.open(photo_path)
photo2 = ImageTk.PhotoImage(photo)
canvas = Canvas(root, height = 400, width = 400)
canvas.create_image(0, 0, image = photo2, anchor = NW)
canvas.pack()

file_path = 'allenamento.txt'
file_path2 = 'check.txt'

line1 = canvas.create_line(0,0, 0, 0)
line2 = canvas.create_line(0,0, 0, 0)
line3 = canvas.create_line(0,0, 0, 0)
line4 = canvas.create_line(0,0, 0, 0)


file1 = open(file_path, 'a')
file2 = open(file_path2, 'a')

def ButtonOnePressed(event):
    global firstPress
    firstPress = event

def ButtonOneReleased(event):
    global lastPress, line1, line2, line3, line4, photo, file1, file2
    lastPress = event
    canvas.delete(line1)
    canvas.delete(line2)
    canvas.delete(line3)
    canvas.delete(line4)
    canvas.pack()
    canvas.update()
    px = photo.load()

    if firstPress.x > lastPress.x:
        temp = firstPress.x
        firstPress.x = lastPress.x
        lastPress.x = temp

    if firstPress.y > lastPress.y:
        temp = firstPress.y
        firstPress.y = lastPress.y
        lastPress.y = temp

    color = input("Colore: ")  # w for WHITE, b for BLACK, g for GREEN, s for SILVER

    #r, g, b = 0, 0, 0

    for i in range(firstPress.x, lastPress.x):
        for j in range(firstPress.y, lastPress.y):
            file2.write(str(px[i, j][0]) + ' ' + str(px[i, j][1]) + ' ' + str(px[i, j][2]) + ' ' + color + '\n')
            #r = r + px[i, j][0]
            #g = g + px[i, j][1]
            #b = b + px[i, j][2]

    #r = int(r/((lastPress.x - firstPress.x) * (lastPress.y - firstPress.y)))
    #g = int(g/((lastPress.x - firstPress.x) * (lastPress.y - firstPress.y)))
    #b = int(b/((lastPress.x - firstPress.x) * (lastPress.y - firstPress.y)))
    #file1.write(str(r) + ' ' + str(g) + ' ' + str(b) + ' ' + color + '\n')


def ButtonOneMotion(event):
    global canvas, line1, line2, line3, line4
    canvas.delete(line1)
    canvas.delete(line2)
    canvas.delete(line3)
    canvas.delete(line4)
    line1 = canvas.create_line(firstPress.x, firstPress.y, event.x, firstPress.y, fill = 'yellow')
    line2 = canvas.create_line(event.x, firstPress.y, event.x, event.y, fill = 'yellow')
    line3 = canvas.create_line(event.x, event.y, firstPress.x, event.y, fill = 'yellow')
    line4 = canvas.create_line(firstPress.x, event.y, firstPress.x, firstPress.y, fill = 'yellow')
    canvas.pack()
    canvas.update()

root.bind('<Button-1>', ButtonOnePressed)

root.bind('<B1-Motion>', ButtonOneMotion)

root.bind('<ButtonRelease-1>', ButtonOneReleased)

root.mainloop()
