#include "CTLVentilo.h"
#include "Config.h"
#include "CTLProtocol.h"
#include "HUBOut.h"
#include "Global.h"

  /*Relay connection:
  RED: UP: NC
  YELLOW: DOWN: NO
  */
  
  /*Direction:
  Clockwise     ->Air to motor  ->Out->direction_pin:HIGH
  Anti-Clockwise->Air from motor->In ->direction_pin:LOW
  */
  
 

  CTLVentilo::CTLVentilo(int _power_pin, int _direction_pin,HUBOut* _hubOut) {
    power_pin = _power_pin;
    direction_pin = _direction_pin;
    hubOut=_hubOut;
  }
  
   void CTLVentilo::setup() {
  }

   void CTLVentilo::on() {
    hubOut->on(power_pin);
    debug("on()");
  }
  
   void CTLVentilo::off() {
    hubOut->off(power_pin);
    debug("off()");
  }

   void CTLVentilo::ping(){
    debug("PING()");
  }
  
  void CTLVentilo::clockWise(){
    off();
    hubOut->on(direction_pin);
    debug("clockWise()");
    standBy();
    on();
  }

  void CTLVentilo::antiClockWise(){
    off();
    hubOut->off(direction_pin);
    debug("antiClockWise()");
    standBy();
    on();
  }
  
  void CTLVentilo::standBy(){
    debug("standBy()");
  //delay(standByMs);
  }

  void CTLVentilo::debug(String message){
    //if(VG_DEBUG){
      Serial.print("CTLVentilo: ");
      Serial.println(message);      
    // }
  }