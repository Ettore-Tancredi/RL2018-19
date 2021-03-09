#include "PID.h"
#include "costanti.h"
#include <Arduino.h>

PID::PID()
{
  Kp = 10;
  Ki = 10;
  Kd = 10;
  E = 0;
  I = 0;
}

PID::PID(double p, double i, double d)
{
  Kp = p;
  Ki = i;
  Kd = d;
  E = 0;
  I = 0;
}

// int PID::pid(int x, int y)
// {
//   double E_prec=E;
//   E = 0;
//   int H = 200;
//   int W = 200;
  
//   y = H/2 - y;
//   x = x - W/2;
//   if (x == 0)
//     return 0;
//   E = -(x / abs(x)) * sqrt(x*x + y*y);
//   if(E == 0)
//     E_prec = 0, I = 0;
//   P = E * Kp;
//   I += E * Ki;
//   D = (E - E_prec) * Kd;

//   return P + I + D;
// }

int PID::pid(double D_x, double D_y)
{
  double E_prec=E;
  E = 0;
  int H = 200;
  int W = 200;
  
  if (D_y)
    E = D_x/D_y;

  if(E == 0)
    E_prec = 0, I = 0;
  P = E * Kp;
  I += E * Ki;
  D = (E - E_prec) * Kd;

  return P + I + D;
}
