#ifndef TOF_H
#define TOF_H

class ToF
{
private:
  int address;
public:
  ToF(int);
  ToF();
  int getDistance();
};

#endif
