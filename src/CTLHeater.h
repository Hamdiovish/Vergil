#ifndef CTLHEATER_H
#define CTLHEATER_H

#include <Arduino.h>
#include "Config.h"
#include "CTLProtocol.h"
//#include "HUBOut.h"
 
class HUBOut;
class CTLHeater: public CTLProtocol {

  private:

    int power_pin;
    int interval=10000;
    int standByMs=5000;

    int idl_temperature;
    int min_temperature;
    int max_temperature;

    HUBOut* hubOut;
    
    boolean enabled;

  public:

    CTLHeater(int _power_pin,int _idl_temperature, int _min_temperature, int _max_temperature,HUBOut* hubOut);

    virtual void setup();
    virtual void on();
    virtual void off() ;
    virtual void ping();
  
    void enable();
    void disable();
    void standBy();
    void debug(String message);
    void debug(double message);

};

#endif
