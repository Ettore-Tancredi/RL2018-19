from PIL import Image
import tkinter as tk

class Filtro():
    def __init__(self, k, img = None):
        self.k = k
        self.img, self.img2 = img, img.copy()

    def filtra(self):
        self.px = self.img.load()
        self.px2 = self.img2.load()
        self.filtroMediano()
        return self.img2

    def visitaAdiacenti(self, x, y):
        x_ad = [0, 1, 1, 1, 0, -1, -1, -1]
        y_ad = [1, 1, 0, -1, -1, -1, 0, 1]
        media = (self.px[x, y][0], self.px[x, y][1], self.px[x, y][2])
        num = 1
        for i in range(0, 8):
            new_x = x + x_ad[i]
            new_y = y + y_ad[i]
            if new_x >= 0 and new_x < self.img.size[0] and new_y >=0 and new_y < self.img.size[1]:
                flag = True
                for j in range(0, 3):
                    if self.px[x, y][j] < (self.px[new_x, new_y][j] - self.k) or self.px[x, y][j] > (self.px[new_x, new_y][j] + self.k):
                        flag = False
                if flag == True:
                    num = num + 1
                    media = (media[0] + self.px[new_x, new_y][0], media[1] + self.px[new_x, new_y][1], media[2] + self.px[new_x, new_y][2])
        media = (int(media[0] / num), int(media[1] / num), int(media[2] / num))
        return media

    def filtroMediano(self):
        for x in range(self.img.size[0]):
            for y in range(self.img.size[1]):
                 self.px2[x, y] = self.visitaAdiacenti(x, y)
