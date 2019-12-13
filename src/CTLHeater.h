#ifndef CTLHEATER_H
#define CTLHEATER_H

#include "Config.h"
#include "SNSDht11.h"
#include "CTLProtocol.h"
#include "HUBOut.h"
 
class CTLHeater: public CTLProtocol {

  private:

    int power_pin;
    int interval=10000;
    int standByMs=5000;

    int idl_temperature;
    int min_temperature;
    int max_temperature;

    HUBOut *hubOut;
    
    boolean enabled=true;

  public:

     CTLHeater(int _power_pin,int _idl_temperature, int _min_temperature, int _max_temperature,HUBOut* _hubOut){
      power_pin = _power_pin;
      idl_temperature = _idl_temperature;
      min_temperature = _min_temperature;
      max_temperature = _max_temperature;
      hubOut=_hubOut;
    }

    virtual void setup() {
    }

    virtual void on() {
      hubOut->on(power_pin);
      debug("on()");
    }
    
    virtual void off() {
      hubOut->off(power_pin);
      debug("off()");
    }

    virtual void ping(){
       debug("ping()");
    }
  
    void enable(){
      debug("enabled()");
      enabled=true;
    }

    void disable(){
      debug("disabled()");
      enabled=false;
    }

    void standBy(){
     debug("standBy()");
     delay(standByMs);
    }

    void debug(String message){
      if(DEBUG){
        Serial.print("CTLHeater: ");
        Serial.println(message);      
      }
    }
    
    void debug(double message){
      if(DEBUG){
        Serial.print("CTLHeater: ");
        Serial.println(message);      
      }
    }

};

#endif
