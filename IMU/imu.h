#ifndef IMU_H
#define IMU_H

#include <Adafruit_BNO055.h>

struct Position
{
  double x;
  double y;
  double z;
};

class IMU:public Adafruit_BNO055
{
//private:
    

public:
  IMU(int something):Adafruit_BNO055(something){};
  Position position;
  void setAngle();
  double getRotationOnX();
  double getRotationOnY();
  double getRotationOnZ();
};

#endif
