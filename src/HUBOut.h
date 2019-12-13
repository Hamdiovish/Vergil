#ifndef HUB_OUT_H
#define HUB_OUT_H

#include "Config.h"

#include <SPI.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>

class HUBOut {

  private:
  
    int ss_latch_pin;
    int count_pin;
    shiftOutX* sr; 

  public:

    HUBOut(int _ss_latch_pin, int _count_pin){
      ss_latch_pin = _ss_latch_pin;
      count_pin = _count_pin;
      
      sr = new shiftOutX( ss_latch_pin, count_pin, MSBFIRST); //SPI
    };
    
  virtual void setup() {
  }
  
  void on(int pin){
    debug("on("+((String)pin)+")");
    sr->pinOn(pin);
  }

  void off(int pin){
    debug("off("+((String)pin)+")");
    sr->pinOff(pin);
  }

  uint8_t getState(int pin){
    return sr->pinState(pin);

  }

  void debug(String message){
    if(DEBUG){
      Serial.print("HUBOut: ");
      Serial.println(message);      
    }
  }
};

#endif
