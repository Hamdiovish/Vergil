#include "sensors/SNSDigital.h"

#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "controllers/CTLMainPump.h"
#include "controllers/CTLSwitchPump.h"
#include "controllers/CTLHeater.h"
#include "controllers/CTLVentilo.h"
#include "controllers/CTLLight.h"

#include <ShiftIn.h>
#include "utilities/Global.h"
#include "utilities/Injector.h"


  SNSDigital::SNSDigital(int _load_pin,int _clock_pin,int _data_pin){
    load_pin  = _load_pin;
    data_pin  = _data_pin;
    clock_pin = _clock_pin;
    interval=INTERVAL_SNS_DGT;
    latestInterval = 0;
  };
  
  void SNSDigital::setup() {
  shift.begin(load_pin, data_pin, clock_pin);
}


  void SNSDigital::loop() {
  if (millis() - latestInterval >= interval) {
      latestInterval=millis();
      if(shift.update()) // read in all values. returns true if any button has changed
        handleUpdates();
  }
}
  
void SNSDigital::handleUpdates() {
    debug("handleUpdates()");
          
    if(shift.hasChanged(SNS_DGT_MAIN_PUMP)){
      debug("SNS_DGT_MAIN_PUMP:");
      debugBoolean(shift.state(SNS_DGT_MAIN_PUMP));
      if (shift.state(SNS_DGT_MAIN_PUMP)==1){     
        ctlMainPump->off();
      }else{
        ctlMainPump->on();
      }      
    }

    if(shift.hasChanged(SNS_DGT_SWITCH_PUMP_TOP)){
      debug("SNS_DGT_SWITCH_PUMP_TOP:");
      debugBoolean(shift.state(SNS_DGT_SWITCH_PUMP_TOP));
      if (shift.state(SNS_DGT_SWITCH_PUMP_TOP)==1){     
        ctlSwitchPump->on();
        ctlMainPump->off();
      }else{
        ctlSwitchPump->off();
      }
    }
  
    if(shift.hasChanged(SNS_DGT_SWITCH_PUMP_BOTTOM)){
      debug("SNS_DGT_SWITCH_PUMP_BOTTOM:");
      debugBoolean(shift.state(SNS_DGT_SWITCH_PUMP_BOTTOM));
      if (shift.state(SNS_DGT_SWITCH_PUMP_BOTTOM)==1){     
        ctlSwitchPump->off();
      }else{
        ctlSwitchPump->on();
      }
    }
  }

void SNSDigital::debug(String message){
  //if(VG_DEBUG){
    Serial.print("SNSDigital String: ");
    Serial.println(message);      
  //}
}

void SNSDigital::debugBoolean(boolean message){
  //if(VG_DEBUG){
    Serial.print("SNSDigital boolean: ");
    Serial.println(message);      
  //}
}

//https://infectedbytes.com/2016/07/arduino-shiftin.html