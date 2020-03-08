#ifndef CTLVENTILO_H
#define CTLVENTILO_H

#include "Config.h"
#include "CTLProtocol.h"
//#include "HUBOut.h"
#include "Global.h"
 
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
    //HUBOut *hubOut;

  public:

    CTLVentilo(int _power_pin, int _direction_pin
    //,HUBOut* _hubOut
    ) {
      power_pin = _power_pin;
      direction_pin = _direction_pin;
      //hubOut=_hubOut;
    }
    
    virtual void setup() {
    }

    virtual void on() {
      //hubOut->on(power_pin);
      debug("on()");
    }
    
    virtual void off() {
      //hubOut->off(power_pin);
      debug("off()");
    }

   virtual void ping(){
     debug("PING()");
   }
   
    void clockWise(){
      off();
      //hubOut->on(direction_pin);
      debug("clockWise()");
      standBy();
      on();
    }

    void antiClockWise(){
      off();
      //hubOut->off(direction_pin);
      debug("antiClockWise()");
      standBy();
      on();
    }
    
    void standBy(){
     debug("standBy()");
     delay(standByMs);
    }

    void debug(String message){
      //if(VG_DEBUG){
        Serial.print("CTLVentilo: ");
        Serial.println(message);      
     // }
    }

};

#endif
