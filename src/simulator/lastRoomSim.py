from tkinter import *
import math
import time
import random

################################################################################
#GLOABAL VARIABLES
################################################################################
#TK VARIABLES
zoom = 5
WIDTH = 90 * zoom
HEIGHT = 120 * zoom
CANVAS_WIDTH = WIDTH + 50
CANVAS_HEIGHT = HEIGHT + 50

root = Tk()
canvas = Canvas(root, height=CANVAS_HEIGHT, width=CANVAS_WIDTH, bg="#ffffcc")
canvas.pack()



#ROOM VARIABLES
corner_x = 10
corner_y = 10
WIDTH = 90 * zoom
HEIGHT = 120 * zoom

corners = [
    [corner_x , corner_y],
    [corner_x , corner_y+HEIGHT],
    [corner_x +WIDTH, corner_y+HEIGHT],
    [corner_x +WIDTH, corner_y],
]

#ROBOT VARIABLES
start_x = 20
start_y = corners[1][1] - 10*zoom

R_WIDTH = 14 * zoom
R_HEIGHT = 7 * zoom
r_vertices = [
    [start_x , start_y],
    [start_x , start_y+R_HEIGHT],
    [start_x +R_WIDTH, start_y+R_HEIGHT],
    [start_x +R_WIDTH, start_y],
]
W_WIDTH = 5 * zoom
W_HEIGHT = 1 * zoom
w1_vertices = [
    [start_x, start_y-W_HEIGHT],
    [start_x , start_y],
    [start_x + W_WIDTH, start_y],
    [start_x +W_WIDTH, start_y-W_HEIGHT],
]
w2_vertices = [
    [start_x, start_y+R_HEIGHT],
    [start_x , start_y+R_HEIGHT+W_HEIGHT],
    [start_x + W_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x +W_WIDTH, start_y+R_HEIGHT],
]
w3_vertices = [
    [start_x+R_WIDTH-W_WIDTH, start_y+R_HEIGHT],
    [start_x+R_WIDTH-W_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x+R_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x+R_WIDTH, start_y+R_HEIGHT],
]
w4_vertices = [
    [start_x+R_WIDTH-W_WIDTH, start_y-W_HEIGHT],
    [start_x+R_WIDTH-W_WIDTH, start_y],
    [start_x+R_WIDTH, start_y],
    [start_x+R_WIDTH, start_y-W_HEIGHT],
]
center = [r_vertices[0][0] + R_WIDTH/2, r_vertices[3][1] + R_HEIGHT/2]
current_angle = 0

#VICTIMS VARIABLES
V_DIAMETER = 5 * zoom
v1_vertices = [
    [20*zoom-V_DIAMETER/2, 10*zoom-V_DIAMETER/2],
    [20*zoom+V_DIAMETER/2, 10*zoom+V_DIAMETER/2],
]
v2_vertices = [
    [10*zoom-V_DIAMETER/2, 20*zoom-V_DIAMETER/2],
    [10*zoom+V_DIAMETER/2, 20*zoom+V_DIAMETER/2],
]
v3_vertices = [
    [30*zoom-V_DIAMETER/2, 30*zoom-V_DIAMETER/2],
    [30*zoom+V_DIAMETER/2, 30*zoom+V_DIAMETER/2],
]
v4_vertices = [
    [50*zoom-V_DIAMETER/2, 45*zoom-V_DIAMETER/2],
    [50*zoom+V_DIAMETER/2, 45*zoom+V_DIAMETER/2],
]
v5_vertices = [
    [40*zoom-V_DIAMETER/2, 60*zoom-V_DIAMETER/2],
    [40*zoom+V_DIAMETER/2, 60*zoom+V_DIAMETER/2],
]

E_SIDE = 20* zoom
evac_vertices = [
    [corner_x, corner_y],
    [corner_x, corner_y+E_SIDE],
    [corner_x+E_SIDE, corner_y]
]
victims_coord = [
    [40*zoom, 60*zoom],
    [50*zoom, 45*zoom],
    [30*zoom, 30*zoom],
    [10*zoom, 20*zoom],
    [20*zoom, 10*zoom],
    [int(corner_x+E_SIDE/2), int(corner_y+E_SIDE/2)]
]
# random.seed()
# for i in range(0, 5):
#     victims_coord[i][0] = random.randint(int(corner_x+V_DIAMETER/2), int(WIDTH-V_DIAMETER/2))
#     victims_coord[i][1] = random.randint(int(corner_y+V_DIAMETER/2), int(HEIGHT-V_DIAMETER/2-R_HEIGHT-80))
#
# v1_vertices = [
#     [victims_coord[0][0]-V_DIAMETER/2, victims_coord[0][1]-V_DIAMETER/2],
#     [victims_coord[0][0]+V_DIAMETER/2, victims_coord[0][1]+V_DIAMETER/2],
# ]
# v2_vertices = [
#     [victims_coord[1][0]-V_DIAMETER/2, victims_coord[1][1]-V_DIAMETER/2],
#     [victims_coord[1][0]+V_DIAMETER/2, victims_coord[1][1]+V_DIAMETER/2],
# ]
# v3_vertices = [
#     [victims_coord[2][0]-V_DIAMETER/2, victims_coord[2][1]-V_DIAMETER/2],
#     [victims_coord[2][0]+V_DIAMETER/2, victims_coord[2][1]+V_DIAMETER/2],
# ]
# v4_vertices = [
#     [victims_coord[3][0]-V_DIAMETER/2, victims_coord[3][1]-V_DIAMETER/2],
#     [victims_coord[3][0]+V_DIAMETER/2, victims_coord[3][1]+V_DIAMETER/2],
# ]
# v5_vertices = [
#     [victims_coord[4][0]-V_DIAMETER/2, victims_coord[4][1]-V_DIAMETER/2],
#     [victims_coord[4][0]+V_DIAMETER/2, victims_coord[4][1]+V_DIAMETER/2],
# ]



################################################################################
#FUNCTIONS
################################################################################

def clear(item):
    canvas.delete(item)

def draw_square(points, color="blue", border=''):
    return canvas.create_polygon(points, fill=color, outline=border)
def draw_circle(points, color="blue", border=''):
    return canvas.create_oval(points, fill=color, outline=border)

def draw_victim(point, color="silver"):
    return canvas.create_oval(points, fill=color, outline=border)

def move(points, distance):
    angle = math.radians(abs(current_angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    for i in range(0, 4):
        points[i][0] = points[i][0] + cos_val * distance
        points[i][1] = points[i][1] + sin_val * -distance

    return points

def movefor(distance):
    global robot
    global w1
    global w2
    global w3
    global w4
    global r_vertices
    global w1_vertices
    global w2_vertices
    global w3_vertices
    global w4_vertices
    for i in range(0, abs(distance)):
        step = 1
        if distance < 0:
            step = -step
        canvas.delete(robot)
        canvas.delete(w1)
        canvas.delete(w2)
        canvas.delete(w3)
        canvas.delete(w4)


        r_vertices = move(r_vertices, step)
        robot = draw_square(r_vertices)
        w1_vertices = move(w1_vertices, step)
        w1 = draw_square(w1_vertices, color="red")
        w2_vertices = move(w2_vertices, step)
        w2 = draw_square(w2_vertices, color="red")
        w3_vertices = move(w3_vertices, step)
        w3 = draw_square(w3_vertices, color="red")
        w4_vertices = move(w4_vertices, step)
        w4 = draw_square(w4_vertices, color="red")

        time.sleep(0.005)
        root.update()
        center[0] = (r_vertices[3][0] + r_vertices[1][0])/2
        center[1] = (r_vertices[3][1] + r_vertices[1][1])/2

def rotate(points, angle, center):
    angle = math.radians(angle)
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = center
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    return new_points

def rotatefor(angle):
    global robot
    global w1
    global w2
    global w3
    global w4
    global r_vertices
    global w1_vertices
    global w2_vertices
    global w3_vertices
    global w4_vertices
    for i in range(0, abs(angle)):
        step = 1
        if angle < 0:
            step = -step
        canvas.delete(robot)
        canvas.delete(w1)
        canvas.delete(w2)
        canvas.delete(w3)
        canvas.delete(w4)

        r_vertices = rotate(r_vertices, step, center)
        robot = draw_square(r_vertices)
        w1_vertices = rotate(w1_vertices, step, center)
        w1 = draw_square(w1_vertices, color="red")
        w2_vertices = rotate(w2_vertices, step, center)
        w2 = draw_square(w2_vertices, color="red")
        w3_vertices = rotate(w3_vertices, step, center)
        w3 = draw_square(w3_vertices, color="red")
        w4_vertices = rotate(w4_vertices, step, center)
        w4 = draw_square(w4_vertices, color="red")
        time.sleep(0.005)
        root.update()
    global current_angle
    current_angle += angle

#instantiate tk objects
room = draw_square(corners, color="white", border="black")
robot = draw_square(r_vertices)
w1 = draw_square(w1_vertices, color="red")
w2 = draw_square(w2_vertices, color="red")
w3 = draw_square(w3_vertices, color="red")
w4 = draw_square(w4_vertices, color="red")

victims = []
victims.append(draw_circle(v5_vertices, color="silver"))
victims.append(draw_circle(v4_vertices, color="silver"))
victims.append(draw_circle(v3_vertices, color="silver"))
victims.append(draw_circle(v2_vertices, color="silver"))
victims.append(draw_circle(v1_vertices, color="silver"))
draw_square(evac_vertices, color="black")

################################################################################
#ACTUAL CODE
################################################################################
root.update()
time.sleep(3)

movefor(WIDTH-R_WIDTH)
rotatefor(-90)



for i in range(0, 5):
    a = center[0] - victims_coord[i][0]
    b = center[1] - victims_coord[i][1]
    new_angle = -int((math.atan(a/b)*(180/math.pi)))
    rotatefor(new_angle)
    dist = int(math.sqrt(a*a+b*b))
    movefor(dist)
    rotatefor(-new_angle)
    if i < 5:
        clear(victims[i])





root.mainloop()
