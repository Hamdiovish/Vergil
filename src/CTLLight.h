#ifndef CTL_LIGHT_H
#define CTL_LIGHT_H

#include "Config.h"
#include "SNSDht11.h"
#include "CTLProtocol.h"
#include "HUBOut.h"
#include "Global.h"
 
class CTLLight: public CTLProtocol {

  private:

    int power_pin;
    HUBOut *hubOut;   
    boolean enabled=true;

  public:

     CTLLight(int _power_pin,HUBOut* _hubOut){
      power_pin = _power_pin;
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

    void debug(String message){
      //if(VG_DEBUG){
        Serial.print("CTL_Light: ");
        Serial.println(message);      
     // }
    }
    
    void debug(double message){
      //if(VG_DEBUG){
        Serial.print("CTL_Light: ");
        Serial.println(message);      
     // }
    }

};

#endif
