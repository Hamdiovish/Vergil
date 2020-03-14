#include "controllers/CTLLight.h"
#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"


CTLLight::CTLLight(int _power_pin){
  power_pin = _power_pin;
}

  void CTLLight::setup() {
}

  void CTLLight::on() {
  hubOut->onRelay(power_pin);
  debug("on()");
}

  void CTLLight::off() {
  hubOut->offRelay(power_pin);
  debug("off()");
}

  void CTLLight::ping(){
    debug("ping()");
}

void CTLLight::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLLight::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLLight::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTL_Light: ");
    Serial.println(message);      
  // }
}

void CTLLight::debug(double message){
  //if(VG_DEBUG){
    Serial.print("CTL_Light: ");
    Serial.println(message);      
  // }
}

