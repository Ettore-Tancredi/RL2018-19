#include "imu.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

void IMU::setAngle()
{
  sensors_event_t event;
  getEvent(&event);

  position.x = event.orientation.x;
  position.y = event.orientation.y;
  position.z = event.orientation.z;
}

double IMU::getRotationOnX()
{
  sensors_event_t event;
  getEvent(&event);
  return event.orientation.x - position.x;
}

double IMU::getRotationOnY()
{
  sensors_event_t event;
  getEvent(&event);
  return event.orientation.y - position.y;
}

double IMU::getRotationOnZ()
{
  sensors_event_t event;
  getEvent(&event);
  return event.orientation.z - position.z;
}
