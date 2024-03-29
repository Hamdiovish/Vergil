#include "controllers/CTLVentilo.h"
#include "utilities/Config.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

  /*Relay connection:
  RED: UP: NC
  YELLOW: DOWN: NO
  */
  
  /*Direction:
  Clockwise     ->Air to motor  ->Out->direction_pin:HIGH
  Anti-Clockwise->Air from motor->In ->direction_pin:LOW
  */
  
 

  CTLVentilo::CTLVentilo(int _power_pin, int _direction_pin) {
    power_pin = _power_pin;
    direction_pin = _direction_pin;
  }
  
   void CTLVentilo::setup() {
  }

   void CTLVentilo::on() {
    hubOut->onRelay(power_pin);
    debug("on()");
  }
  
   void CTLVentilo::off() {
    hubOut->offRelay(power_pin);
    debug("off()");
  }

   void CTLVentilo::ping(){
    debug("PING()");
  }
  
  void CTLVentilo::clockWise(){
    off();
    hubOut->onRelay(direction_pin);
    debug("clockWise()");
    standBy();
    on();
  }

  void CTLVentilo::antiClockWise(){
    off();
    hubOut->offRelay(direction_pin);
    debug("antiClockWise()");
    standBy();
    on();
  }
  
  void CTLVentilo::standBy(){
    debug("standBy()");
    delay(standByMs);
  }

  void CTLVentilo::debug(String message){
    //if(VG_DEBUG){
      Serial.print("CTLVentilo: ");
      Serial.println(message);      
    // }
  }