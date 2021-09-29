#ifndef LM_h
#define LM_h
#include "Arduino.h"

class LM

{

  public:
    LM();
    float readTemperature();
    void printOut();
    void deepSleep();
 
 
  private:
    int analog_value = 0;
    double temp = 0;

};

/***************************************************/

#endif
