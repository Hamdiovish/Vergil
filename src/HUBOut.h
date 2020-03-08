#ifndef HUB_OUT_H
#define HUB_OUT_H

#include "Config.h"
#include "CTLRtc.h"

#include <SPI.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
#include "SNSDht11Light.h"

class HUBOut {

  private:
  
    int ss_latch_pin;
    int count_pin;
    shiftOutX* sr; 

    int buzzer_pin;
    boolean buzzing=false;
    uint32_t buzzerInterval;
    uint32_t buzzerLatestInterval;

  public:
    SNSDht11Light* dht11;
    CTLRtc* rtc;
    
    HUBOut(){

    }

    HUBOut(int _ss_latch_pin, int _count_pin, int _buzzer_pin, CTLRtc* _rtc, SNSDht11Light* _dht11){
      ss_latch_pin = _ss_latch_pin;
      count_pin = _count_pin;
      rtc=_rtc;

      sr = new shiftOutX( ss_latch_pin, count_pin, MSBFIRST); //SPI

      buzzer_pin = _buzzer_pin;
      buzzerInterval=INTERVAL_CTL_BUZZER;
      dht11=_dht11;
    };
    
  virtual void setup() {
    this->allOff();
  }
  
  void on(int pin){
    debug("on("+((String)pin)+")");
    sr->pinOn(pin);
  }

  void off(int pin){
    debug("off("+((String)pin)+")");
    sr->pinOff(pin);
  }

  void allOff(){
    sr->allOff();
  }

  void allOn(){
    sr->allOn();
  }

  uint8_t getState(int pin){
    return sr->pinState(pin);

  }

  void debug(String message){
    if(DEBUG){
      Serial.print("HUBOut: ");
      Serial.println(message);      
    }
  }

  void treatBuzzer(){
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

  void buzz() {
    buzzing=true;
    debug("buzz()");
  }

  void updateTime(long time){
      this->rtc->updateTime(time);
  }
  
  void displayTime(char* data){
      debug("displayTime()");
      this->rtc->getTimeFormatted(data);
  }

  void loop(){
    treatBuzzer();
  }

};

#endif
