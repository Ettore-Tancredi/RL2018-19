import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import numpy as np
import numpy

#"card" graph. See README for details
def card(arr, savename, H, W):

    img_val = []
    x_val = []
    y_val = []

#list of possible unique elements
    comp = []
    for i in range(0, 27):
        comp.append(0)

#count element occurence
    for i in range(0, H):
        for j in range(0, W):
            val = int((int(arr[i][j][0]) + int(arr[i][j][1]) + int(arr[i][j][2])) / 3)
            rem = val%10
            if rem >= 5:
                img_val.append(val + (10 - rem))
            else:
                img_val.append(val - rem)

    for i in range(0, len(img_val)):
        comp[int(img_val[i]/10)] = comp[int(img_val[i]/10)] + 1
        y_val = [y for y in comp if y > 0]

    for i in range(0, len(comp)):
        if comp[i] > 0:
            x_val.append(i*10);

#plot results
    plt.plot(x_val, y_val, 'ro')
    plt.show()
    plt.savefig(savename)


#"map" graph. See README for details
def graph_map(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            val = int((int(arr[i][j][0]) + int(arr[i][j][1]) + int(arr[i][j][2])) / 3)
            rem = val%10
            if rem >= 5:
                #transpose for correct plotting
                z_val[j][i] = val + (10 - rem)
            else:
                z_val[j][i] = val - rem
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()
    # plt.savefig(savename)

    #"map" graph. See README for details
def graph_mapB(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            val = arr[i][j][2]
            rem = val%10
            if rem >= 5:
                #transpose for correct plotting
                z_val[j][i] = val + (10 - rem)
            else:
                z_val[j][i] = val - rem
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()
    # plt.savefig(savename)

    #"map" graph. See README for details
def graph_mapR(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            val = arr[i][j][0]
            rem = val%10
            if rem >= 5:
                #transpose for correct plotting
                z_val[j][i] = val + (10 - rem)
            else:
                z_val[j][i] = val - rem
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()
    # plt.savefig(savename)


#"wir" graph. See README for details.
def graph_wir(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            val = int((int(arr[i][j][0]) + int(arr[i][j][1]) + int(arr[i][j][2])) / 3)
            rem = val%10
            if rem >= 5:
                #transpose for correct plotting
                z_val[j][i] = val + (10 - rem)
            else:
                z_val[j][i] = val - rem

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_wireframe(X, Y, Z)
    plt.show()
    # plt.savefig(savename)


    #"map" graph. See README for details
def graph_mapG(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            #transpose for correct plotting
            z_val[j][i] = arr[i][j][1]

    fig = plt.figure()

    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()
    # plt.savefig(savename)


    #"wir" graph. See README for details.
def graph_wirG(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            #transpose for correct plotting
            z_val[j][i] = arr[i][j][1]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_wireframe(X, Y, Z)
    plt.show()
    # plt.savefig(savename)
def maxv(a, b, c):
	if a > b and a > c:
		return a
	elif b > a and b > c:
		return b
	else:
		return c


def minv(a, b, c):
	if a < b and a < c:
		return a
	elif b < a and b < c:
		return b
	else:
		return c

def graph_diffB(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            #transpose for correct plotting
            z_val[j][i] = abs(arr[i][j][3] - arr[i][j][1])

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()

def graph_diffR(arr, savename, H, W):
    x = range(W)
    y = range(H)

    z_val = [0] * H
    for i in range(H):
        z_val[i] = [0] * W

    for i in range(0, H):
        for j in range(0, W):
            #transpose for correct plotting
            z_val[j][i] = abs(arr[i][j][0] - arr[i][j][1])

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y = numpy.meshgrid(x, y)
    Z = np.matrix(z_val)
    ax.plot_surface(X, Y, Z)
    plt.show()

def color(R, G, B):
    if ((R + G + B)/3 < 110) and (maxv(R, G, B) - minv(R, G, B) >= 25):
        return 0
    elif (R + G + B)/3 > 65:
        return 1
    elif ((R + G + B)/3 <= 65) and (maxv(R, G, B) - minv(R, G, B) <= 15):
        return 2

def graph_prc(arr, savename, H, W):

    black_px = 0
    white_px = 0
    green_px = 0

    for i in range(H):
        for j in range(W):
            if color(arr[i][j][0], arr[i][j][1], arr[i][j][2]) == 0:
                green_px = green_px + 1;
            elif color(arr[i][j][0], arr[i][j][1], arr[i][j][2]) == 1:
                white_px = white_px + 1;
            elif color(arr[i][j][0], arr[i][j][1], arr[i][j][2]) == 2:
                black_px = black_px + 1;

    tot = black_px + white_px + green_px
    plt.pie([black_px*100/tot, white_px*100/tot, green_px*100/tot])
    plt.show()
    plt.savefig(savename)
