#ifndef PID_H
#define PID_H

class PID{
  private:
    double Kp, Ki, Kd;
    double P, I, D, E;
  public:
    PID();
    PID(double, double, double);
    int pid(double, double);
};

#endif
