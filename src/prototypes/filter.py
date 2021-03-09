from tkinter import *
from PIL import Image

path = "/home/luigi/source/repos/rescueline/src/figures/frames/frame6.png"
img = Image.open(path, 'r')
imgCopy = img.copy()
imgCopy2 = img.copy()
px = img.load()
pxCopy = imgCopy.load()
pxCopy2 = imgCopy2.load()

def visitaAdiacenti(x, y):
    x_ad = [0, 1, 1, 1, 0, -1, -1, -1]
    y_ad = [1, 1, 0, -1, -1, -1, 0, 1]
    media = (px[x, y][0], px[x, y][1], px[x, y][2])
    num = 1
    for i in range(0, 8):
        new_x = x + x_ad[i]
        new_y = y + y_ad[i]
        if new_x >= 0 and new_x < img.size[0] and new_y >=0 and new_y < img.size[1]:
            num = num + 1
            media = (media[0] + px[new_x, new_y][0], media[1] + px[new_x, new_y][1], media[2] + px[new_x, new_y][2])
    media = (int(media[0] / num), int(media[1] / num), int(media[1] / num))
    return media

k = 5
def visitaAdiacenti2(x, y):
    x_ad = [0, 1, 1, 1, 0, -1, -1, -1]
    y_ad = [1, 1, 0, -1, -1, -1, 0, 1]
    media = (px[x, y][0], px[x, y][1], px[x, y][2])
    num = 1
    for i in range(0, 8):
        new_x = x + x_ad[i]
        new_y = y + y_ad[i]
        if new_x >= 0 and new_x < img.size[0] and new_y >=0 and new_y < img.size[1]:
            flag = True
            for j in range(0, 3):
                if px[x, y][j] < px[new_x, new_y][j] - k and px[x, y][j] > px[new_x, new_y][j] + k:
                    flag = False
            if flag == True:
                num = num + 1
                media = (media[0] + px[new_x, new_y][0], media[1] + px[new_x, new_y][1], media[2] + px[new_x, new_y][2])
    media = (int(media[0] / num), int(media[1] / num), int(media[1] / num))
    return media


for x in range(img.size[0]):
    for y in range(img.size[1]):
        pxCopy[x, y] = visitaAdiacenti(x, y)


for x in range(img.size[0]):
    for y in range(img.size[1]):
        pxCopy2[x, y] = visitaAdiacenti2(x, y)

imgCopy.show()
img.show()
imgCopy2.show()

