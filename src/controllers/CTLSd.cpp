#include "controllers/CTLSd.h"
#include "utilities/Config.h"
#include <SPI.h>
#include <SD.h>


CTLSd::CTLSd(int _ss_pin){
  ss_pin = _ss_pin;
}

  void CTLSd::setup() {
  debug("setup()");
  digitalWrite(ss_pin,HIGH);
  if (!SD.begin(ss_pin)) {
    debug("initialization failed!");
  }
  debug("initialization done.");
}

void CTLSd::ping(){
    debug("ping()");
}

void CTLSd::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLSd::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLSd::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTLSd: ");
    Serial.println(message);      
  //}
}

void CTLSd::debug(double message){
  //if(VG_DEBUG){
    Serial.print("CTLSd: ");
    Serial.println(message);      
  //}
}
