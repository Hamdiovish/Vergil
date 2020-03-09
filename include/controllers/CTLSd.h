#ifndef CTL_SD_H
#define CTL_SD_H

#include "utilities/Config.h"
#include <SPI.h>
#include <SD.h>

class CTLSd {

  private:

    int ss_pin;
    boolean enabled=true;
  public:

     CTLSd(int _ss_pin);

     void setup();

    void ping();
  
    void enable();

    void disable();

    void debug(String message);
    
    void debug(double message);

};

#endif
