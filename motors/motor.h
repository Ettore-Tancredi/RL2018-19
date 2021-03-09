#ifndef MOTOR_H
#define MOTOR_H

#include "imu.h"

class Motors
{
private:
  int sxINA, sxENA, sxINB, sxENB, sxPWM, sxCS, dxINA, dxENA, dxINB, dxENB, dxPWM, dxCS;
  void runSx(int);
  void runDx(int);
  
public:
  Motors(int, int, int, int, int, int, int, int, int, int, int, int);
  IMU imu = IMU(55);
  void drive(int, int);
  void turn(double);
  void stop();
};

#endif
