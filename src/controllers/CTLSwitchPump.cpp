#include "controllers/CTLSwitchPump.h"
#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"

CTLSwitchPump::CTLSwitchPump(int _power_pin){
  power_pin = _power_pin;
}

  void CTLSwitchPump::setup() {
}

  void CTLSwitchPump::on() {
  hubOut->on(power_pin);
  debug("on()");
}

  void CTLSwitchPump::off() {
  hubOut->off(power_pin);
  debug("off()");
}

 void CTLSwitchPump::ping(){
    debug("ping()");
}

void CTLSwitchPump::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLSwitchPump::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLSwitchPump::debug(String message){
    //if(VG_DEBUG){
      Serial.print("CTLSwitchPump: ");
      Serial.println(message);      
    //}
}

