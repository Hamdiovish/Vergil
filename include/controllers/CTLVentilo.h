#ifndef CTLVENTILO_H
#define CTLVENTILO_H

#include <Arduino.h>
#include "utilities/Config.h"
#include "protocols/CTLProtocol.h"

//#include "HUBOut.h"
 
 class HUBOut;
 class CTLVentilo:public CTLProtocol {

  private:

    /*Relay connection:
    RED: UP: NC
    YELLOW: DOWN: NO
    */
    
    /*Direction:
    Clockwise     ->Air to motor  ->Out->direction_pin:HIGH
    Anti-Clockwise->Air from motor->In ->direction_pin:LOW
    */
    
  int direction_pin;
  int power_pin;
  int standByMs=5000;
  HUBOut* hubOut;


  public:

    CTLVentilo(int _power_pin, int _direction_pin);
    
    virtual void setup();

    virtual void on();
    
    virtual void off();

   virtual void ping();
   
    void clockWise();

    void antiClockWise();
    
    void standBy();

    void debug(String message);

};

#endif
