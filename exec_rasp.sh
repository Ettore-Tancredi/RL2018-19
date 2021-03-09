#!/bin/bash

cp /home/pi/repos/rescueline/src/control/*.py /home/pi/repos/rescueline/exec
#cp /home/pi/repos/rescueline/src/evac_algorithm/*.py /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/line_algorithm/*.py /home/pi/repos/rescueline/exec
#cp /home/pi/repos/rescueline/src/evac_algorithm/*.so /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/line_algorithm/*.so /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/log/*.py /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/comm/*.py /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/camera/*.py /home/pi/repos/rescueline/exec
cp /home/pi/repos/rescueline/src/kNN/color_data.txt /home/pi/repos/rescueline/exec



cp /home/pi/repos/rescueline/src/control/main.ino /home/pi/Arduino/main/
cp /home/pi/repos/rescueline/src/PID/*PID* /home/pi/Arduino/main/
cp /home/pi/repos/rescueline/src/IMU/*imu* /home/pi/Arduino/main/
cp /home/pi/repos/rescueline/src/motors/*motor* /home/pi/Arduino/main/
cp /home/pi/repos/rescueline/src/control/costanti.h /home/pi/Arduino/main/
cp /home/pi/repos/rescueline/src/comm/usb.h /home/pi/Arduino/main/

