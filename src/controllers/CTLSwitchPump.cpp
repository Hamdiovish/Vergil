#include "controllers/CTLSwitchPump.h"
#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

CTLSwitchPump::CTLSwitchPump(int _power_pin){
  power_pin = _power_pin;
}

  void CTLSwitchPump::setup() {
}

  void CTLSwitchPump::on() {
  hubOut->onRelay(power_pin);
  debug("on()");
}

  void CTLSwitchPump::off() {
  hubOut->offRelay(power_pin);
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


