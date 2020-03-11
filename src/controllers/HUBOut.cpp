#include "controllers/HUBOut.h"

#include <SPI.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "controllers/CTLRtc.h"

#include "sensors/SNSMhz19.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"


HUBOut::HUBOut(int _ss_latch_pin, int _count_pin, int _buzzer_pin){
  ss_latch_pin = _ss_latch_pin;
  count_pin = _count_pin;

  sr = new shiftOutX( ss_latch_pin, count_pin, MSBFIRST); //SPI

  buzzer_pin = _buzzer_pin;
  buzzerInterval=INTERVAL_CTL_BUZZER;
};

  void HUBOut::setup() {
  this->allOff();
}

void HUBOut::on(int pin){
  debug("on("+((String)pin)+")");
  sr->pinOn(pin);
}

void HUBOut::off(int pin){
  debug("off("+((String)pin)+")");
  sr->pinOff(pin);
}

void HUBOut::allOff(){
  sr->allOff();
}

void HUBOut::allOn(){
  sr->allOn();
}

uint8_t HUBOut::getState(int pin){
  return sr->pinState(pin);

}

void HUBOut::debug(String message){
  //if(VG_DEBUG){
    Serial.print("HUBOut: ");
    Serial.println(message);      
  // }
}

void HUBOut::treatBuzzer(){
      if(buzzing){
        on(buzzer_pin);
        if (millis() - buzzerLatestInterval >= buzzerInterval) {
          off(buzzer_pin);
          buzzing=false;
        } 
      }else {
        buzzerLatestInterval=millis();
      }
}

void HUBOut::buzz() {
  buzzing=true;
  debug("buzz()");
}

void HUBOut::updateTime(long time){
    ctlRtc->updateTime(time);
}

void HUBOut::displayTime(char* data){
    debug("displayTime()");
    ctlRtc->getTimeFormatted(data);
}

void HUBOut::loop(){
  treatBuzzer();
}

