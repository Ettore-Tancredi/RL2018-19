from PIL import Image

class Drawings():
    def __init__(self, img, color = (0, 0, 0), k = 20, k2 = 20):
        self.img = img
        self.px = img.load()
        self.k = k
        self.k2 = k2
        self.color = color

    def isOnBorder(self, coordinates):
        if coordinates[0] == 0 or coordinates[0] == self.img.width-1 or coordinates[1] == 0 or coordinates[1] == self.img.height-1:
            return True
        else:
            return False

    def isInside(self, coordinates):
        if coordinates[0] < 0 or coordinates[0] >= self.img.width or coordinates[1] < 0 or coordinates[1] >= self.img.height:
            return False
        else:
            return True

    def isSimilar(self, coordinates):
        diff_rg = self.color[0] - self.color[1]
        diff_gb = self.color[1] - self.color[2]
        diff_rg_c = self.px[coordinates[0], coordinates[1]][0] - self.px[coordinates[0], coordinates[1]][1]
        diff_gb_c = self.px[coordinates[0], coordinates[1]][1] - self.px[coordinates[0], coordinates[1]][2]
        media = (self.color[0] + self.color[1] + self.color[2]) / 3
        media_c = (self.px[coordinates[0], coordinates[1]][0] + self.px[coordinates[0], coordinates[1]][1] + self.px[coordinates[0], coordinates[1]][2]) / 3
        if diff_rg > diff_rg_c - self.k and diff_rg < diff_rg_c + self.k:
            if diff_gb > diff_gb_c - self.k and diff_gb < diff_gb_c + self.k:
                if media > media_c - self.k2 and media < media_c + self.k2:
                    return True
        return False

    def isOnMargin(self, coordinates):
        flag = False
        x_ad = [0, 1, 1, 1, 0, -1, -1, -1]
        y_ad = [1, 1, 0, -1, -1, -1, 0, 1]
        for i in range(0, 8):
            c = (coordinates[0] + x_ad[i], coordinates[1] + y_ad[i])
            if not self.isSimilar(c):
                flag = True
        return (flag and self.isSimilar(coordinates))

    def isValid(self, coordinates):
        if self.isOnBorder(coordinates):
            if self.isSimilar(coordinates):
                return True
        else:
            if self.isOnMargin(coordinates):
                return True
        return False

    def draw(self):
        img2 = self.img.copy()
        px2 = img2.load()
        for x in range(0, self.img.width):
            for y in range(0, self.img.height):
                if self.isValid((x, y)):
                    px2[x, y] = (255, 255, 0)
        return img2