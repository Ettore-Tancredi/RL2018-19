#include "Arduino.h"
#include "motor.h"
#include "usb.h"
#include "PID.h"
#include "costanti.h"
#include "ToF.h"

int M1_pwm = 10;
int M1_in1 = 11;
int M1_in2 = 12;

int M2_pwm = 6;
int M2_in1 = 7;
int M2_in2 = 8;

const int COSO = 0; // costante oscena a caso che possiamo tenere nel codice per occupare i pin delle flag ch enon utilizziamo in attesa dei nuovi ponti H

//GLOBAL OBJECTS
Motors motors(M2_in1, COSO, M2_in2, COSO, M2_pwm, COSO, M1_in2, COSO, M1_in1, COSO, M1_pwm, COSO);
PID Pid = PID(3,2,0);
ToF tof();   // Wire.begin() may cause problems because it's already been called or it'll be recalled

void setup()
{
  Serial.begin(9600);
  motors.imu.begin();
}

char start_char, end_char, case_char;
int X, Y;
int correction;

int i = 0;
int del = 0;
char garbage;

void loop()
{

  start_char = read_char();

  while(start_char != 's')
    start_char = read_char();
  
  case_char = read_char();
  switch(case_char)
  {
    case 'S':
      X = read_int();
      Y = read_int();
      //Serial.print(X);
      //Serial.print(" ");
      //Serial.println(Y);
      //delay(10000);
      correction = Pid.pid(X, Y);
      motors.drive(STD_SPEED - correction, STD_SPEED + correction);
      delay(100);
      motors.stop();
      break;
    case 'I':
      motors.drive(-STD_SPEED, -STD_SPEED);
      delay(100);
      motors.stop();
      break;
    case 'T':
      motors.drive(STD_SPEED, STD_SPEED);
      delay(100);
      motors.stop();
      break;
    case 'C':
      motors.drive(STD_SPEED, STD_SPEED);
      delay(100);
      motors.stop();
      break;
    case 'B':
      motors.turn(180);
      motors.stop();
      break;
    case 'L':
      motors.drive(STD_SPEED, STD_SPEED);
      delay(80);
      motors.stop();
      motors.turn(90);  //valori totalmente arbitrari
      break;
    case 'R':
      motors.drive(STD_SPEED, STD_SPEED);
      delay(80);
      motors.stop();
      motors.turn(90);  //valori totalmente arbitrari
      break;
    default:
      Serial.println("Transmission error1");
      break;
  }
  
    end_char = read_char();
    
    if(end_char != 'e')
      Serial.println("Transmission error2");
  
  
  delay(STOP_DURATION);   //da definire
  

  if(tof.getDistance() < MIN_DIST)
  {
    motors.turn(90);

    motors.drive(STD_SPEED, STD_SPEED);
    delay(1500);   //dealy time has to be set
    motors.stop();

    motors.turn(-90);

    motors.drive(STD_SPEED, STD_SPEED);
    delay(2000);   //dealy time has to be set
    motors.stop();

    motors.turn(-90);

    motors.drive(STD_SPEED, STD_SPEED);
    delay(1500);   //dealy time has to be set
    motors.stop();

    motors.turn(90);
    
    empty_buffer();
  }
  

 
/*
  motors.turn(90);
  delay(200);
  motors.turn(-90);*/
  //motors.stop()
 // delay(5000);
}
