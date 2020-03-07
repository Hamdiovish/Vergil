#ifndef HUB_OUT_H
#define HUB_OUT_H

#include "Config.h"

#include <SPI.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>

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

    HUBOut(int _ss_latch_pin, int _count_pin, int _buzzer_pin){
      ss_latch_pin = _ss_latch_pin;
      count_pin = _count_pin;
      sr = new shiftOutX( ss_latch_pin, count_pin, MSBFIRST); //SPI

      buzzer_pin = _buzzer_pin;
      buzzerInterval=INTERVAL_CTL_BUZZER;
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

  void loop(){
    treatBuzzer();
  }

};

#endif
