#include "controllers/CTLMainPump.h"
#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"


CTLMainPump::CTLMainPump(int _power_pin){
  power_pin = _power_pin;
}

  void CTLMainPump::setup() {}

  void CTLMainPump::on() {
  hubOut->onRelay(power_pin);
  debug("on()");
}

void CTLMainPump::off() {
  hubOut->offRelay(power_pin);
  debug("off()");
}

void CTLMainPump::ping(){
    debug("ping()");
}

void CTLMainPump::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLMainPump::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLMainPump::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTL_MainPump: ");
    Serial.println(message);      
  // }
}

void CTLMainPump::debug(double message){
  //if(VG_DEBUG){
    Serial.print("CTL_MainPump: ");
    Serial.println(message);      
  // }
}

