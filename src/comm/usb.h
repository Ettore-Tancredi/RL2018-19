#ifndef USB_H
#define USB_H

#include "Arduino.h"

int read_int()
{
  int num=0;
  while(!Serial.available()){};
  char c = '0';

 // c = Serial.read();
  while(c!='\n'){
    num= num * 10 + c - '0';
    if(Serial.available())
      c = Serial.read();
    while(!Serial.available()){};
  }

  
  return num;
}

char read_char()
{
  char c;
  while(!Serial.available()){};
  c = Serial.read();
  return c;
}

void empty_buffer()
{
  char garbage;
  while(Serial.available())
    garbage = Serial.read();
}


#endif
