#ifndef CTL_SD_H
#define CTL_SD_H

#include "Config.h"
#include <SPI.h>
#include <SD.h>

class CTLSd {

  private:

    int ss_pin;
    boolean enabled=true;
    CTLLcd* lcd;
  public:

     CTLSd(int _ss_pin,CTLLcd* _lcd){
      ss_pin = _ss_pin;
      lcd = _lcd;
    }

     void setup() {
      debug("setup()");
      digitalWrite(ss_pin,HIGH);
      if (!SD.begin(ss_pin)) {
        debug("initialization failed!");
        lcd->printAt(0,1,"Setup SD failed!");
        while (1);
      }
      debug("initialization done.");
      lcd->printAt(0,1,"Setup SD done!");
    }

    void ping(){
       debug("ping()");
    }
  
    void enable(){
      debug("enabled()");
      enabled=true;
    }

    void disable(){
      debug("disabled()");
      enabled=false;
    }

    void debug(String message){
      if(DEBUG){
        Serial.print("CTLSd: ");
        Serial.println(message);      
      }
    }
    
    void debug(double message){
      if(DEBUG){
        Serial.print("CTLSd: ");
        Serial.println(message);      
      }
    }

};

#endif
