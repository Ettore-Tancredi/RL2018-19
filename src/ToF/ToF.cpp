#include "ToF.h"
#include "Wire.h"

ToF::ToF(int A)
{
  address = A;
  Wire.begin();   //bisogna stare attenti perchè probabilmente è già richiamata nella libreria per l'imu e non so se questo potrebbe creare casini
}

ToF::ToF()
{
  address = 0x10;
  Wire.begin();
}

int ToF::getDistance()
{
  Wire.beginTransmission(address);
  Wire.write("D");
  Wire.endTransmission();
  Wire.requestFrom(address, 2);
  int Distance = ( Wire.read()<<8 | Wire.read() );  
  return Distance;  // distance expressed in mm
}
