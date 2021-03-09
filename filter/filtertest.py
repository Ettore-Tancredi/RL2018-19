import colori2 as clr
from PIL import Image
import random

#immagine = Image.new("RGB", (300, 300))
immagine = Image.open("C:/Users/UTENTE/Documents/OII/colori/grattacielo.jpg")
px = immagine.load()

#for x in range(0, immagine.size[0]):
#    for y in range(0, immagine.size[1]):
#        if random.randint(0, 100) == 10:
#            px[x, y] = (50, 50, 50)
#        else:
#            px[x, y] = (150, 200, 50)

#immagine.save("C:/Users/UTENTE/Documents/OII/colori/esempio.jpeg")
immagine.show()
mioFiltro = clr.Filtro(10, immagine)
mioFiltro.filtra().save("C:/Users/UTENTE/Desktop/prima.jpg")
mioFiltro = clr.Filtro(150, immagine)
mioFiltro.filtra().save("C:/Users/UTENTE/Desktop/seconda.jpg")

im1 = Image.open("C:/Users/UTENTE/Desktop/prima.jpg")
im2 = Image.open("C:/Users/UTENTE/Desktop/seconda.jpg")
px1 = im1.load()
px2 = im2.load()
c = 0
for x in range(0, im1.size[0]):
    for y in range(0, im1.size[1]):
        if px1[x, y] != px2[x, y]:
            c = c + 1

print (c / (im1.size[0]*im2.size[1]) * 100)
