#include "CTLHeater.h"
#include "Config.h"
#include "CTLProtocol.h"
#include "HUBOut.h"
#include "Global.h"
 

  CTLHeater::CTLHeater(int _power_pin,int _idl_temperature, int _min_temperature, int _max_temperature
  //,HUBOut* _hubOut
  ){
    power_pin = _power_pin;
    idl_temperature = _idl_temperature;
    min_temperature = _min_temperature;
    max_temperature = _max_temperature;
    enabled=true;
    //hubOut=_hubOut;
}

  void CTLHeater::CTLHeater::setup() {
}

  void CTLHeater::CTLHeater::on() {
  //hubOut->on(power_pin);
  debug("on()");
}

  void CTLHeater::CTLHeater::off() {
  //hubOut->off(power_pin);
  debug("off()");
}

  void CTLHeater::ping(){
    debug("ping()");
}

void CTLHeater::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLHeater::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLHeater::standBy(){
  debug("standBy()");
  delay(standByMs);
}

void CTLHeater::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTLHeater: ");
    Serial.println(message);      
  //}
}

void CTLHeater::debug(double message){
  //if(VG_DEBUG){
    Serial.print("CTLHeater: ");
    Serial.println(message);      
  //}


};