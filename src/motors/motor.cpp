
#include <Arduino.h>
#include "imu.h"
#include "motor.h"
#include "costanti.h"

Motors::Motors(int sxINAp, int sxENAp /*da ignorare*/, int sxINBp, int sxENBp, int sxPWMp, int sxCSp, int dxINAp, int dxENAp, int dxINBp, int dxENBp, int dxPWMp, int dxCSp) : sxINA(sxINAp), sxENA(sxENAp), sxINB(sxINBp), sxENB(sxENBp), sxPWM(sxPWMp), sxCS(sxCSp), dxINA(dxINAp), dxENA(dxENAp), dxINB(dxINBp), dxENB(dxENBp), dxPWM(dxPWMp), dxCS(dxCSp)
{
  pinMode(sxINAp, OUTPUT);
  pinMode(sxENAp, INPUT);
  pinMode(dxINAp, OUTPUT);
  pinMode(dxENAp, INPUT);
  pinMode(sxINBp, OUTPUT);
  pinMode(sxENBp, INPUT);
  pinMode(dxINBp, OUTPUT);
  pinMode(dxENBp, INPUT);
  pinMode(sxPWMp, OUTPUT);
  pinMode(dxPWMp, OUTPUT);
  pinMode(sxCSp, INPUT);
  pinMode(dxCSp, INPUT);
}

void Motors::stop()
{
  digitalWrite(sxINA, LOW);
  digitalWrite(dxINA, LOW);
  digitalWrite(sxINB, LOW);
  digitalWrite(dxINB, LOW);
}

void Motors::runSx(int speed)
{
  if(speed >= 0)
  {
    digitalWrite(sxINA, LOW);
    digitalWrite(sxINB, HIGH);
    analogWrite(sxPWM, speed);
  }
  else
  {
    digitalWrite(sxINA, HIGH);
    digitalWrite(sxINB, LOW);
    analogWrite(sxPWM, -speed);
  }
}

void Motors::runDx(int speed)
{
  if(speed >= 0)
  {
    digitalWrite(dxINA, LOW);
    digitalWrite(dxINB, HIGH);
   
    analogWrite(dxPWM, speed);
  }
  else
  {
    digitalWrite(dxINA, HIGH);
    digitalWrite(dxINB, LOW);
    analogWrite(dxPWM, -speed);
  }
}

void Motors::drive(int sxSpeed, int dxSpeed)
{
  if (abs(sxSpeed) > MAX_SPEED)
    sxSpeed = (abs(sxSpeed)/sxSpeed) * MAX_SPEED;
  if (abs(sxSpeed) < MIN_SPEED)
    sxSpeed = (abs(sxSpeed)/sxSpeed) * STD_SPEED;
  if (abs(dxSpeed) > MAX_SPEED)
    dxSpeed = (abs(dxSpeed)/dxSpeed) * MAX_SPEED;
  if (abs(dxSpeed) < MIN_SPEED)
    dxSpeed = (abs(dxSpeed)/dxSpeed) * STD_SPEED; 
  runSx(sxSpeed);
  runDx(dxSpeed);  
}
/*
void Motors::turn(double angle)
{
  if(angle < 0)
    angle = 360 + angle;
  double tempRotation = 0;
  imu.setAngle();
  double sign = abs(angle)/angle;
  while(tempRotation < abs(angle))
  {
    tempRotation = imu.getRotationOnX();
    drive(-sign*STD_SPEED, sign*STD_SPEED);     // STD_SPEED da dichiarare in un file di costanti
  }    
  stop();
}*/
void Motors::turn(double angle)
{
  imu.setAngle();

  int sign = angle / abs(angle);
  
  double rotation = abs(imu.getRotationOnX());
  if(rotation > 180)
    rotation = 360 - rotation;

  while(rotation < abs(angle))
  {
    drive(sign * STD_SPEED, -sign * STD_SPEED);
    rotation = abs(imu.getRotationOnX());
    if(rotation > 180)
      rotation = 360 - rotation;
    //delay(10)  ?
  }

  stop();
}
