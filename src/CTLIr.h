#ifndef CTL_IR_H
#define CTL_IR_H

#include "Config.h"
#include "CTLLcd.h"
#include <IRremote.h>
#include "HUBOut.h"

class CTLIr {

  private:

    boolean enabled=true;
    int data_pin;
    IRrecv* ir;
    decode_results results;
    HUBOut* hubOut;
    CTLRtc* rtc;
    CTLLcd* lcd;
  public:

    CTLIr(int _data_pin,CTLLcd* _lcd,CTLRtc* _rtc,HUBOut* _hubOut){
      data_pin=_data_pin;
      hubOut=_hubOut;
      rtc=_rtc;
      lcd=_lcd;
    }

    void setup() {
      debug("setup()");
      ir=new IRrecv(data_pin);
      ir->enableIRIn();
      hubOut->lcd->printAt(0,1,"Setup IR done!  ");
    }

    void loop(){
      if (ir->decode(&results)){
        switch(results.value){
          case 0xFFC23D:{ //Recep button FFC23D "Stop/Resume"
            debug(">>0xFFC23D:");
            hubOut->buzz();
            if(SERIAL_ENABLED){
                SERIAL_ENABLED=false;
                Serial.end();
              }else{
                SERIAL_ENABLED=true;
                Serial.begin(9600);
              }
            break;
            };
            case 0xFF906F:{
              debug(">>0xFF906F:");
              hubOut->buzz();
              hubOut->displayTime();        
              break;
            };
        }
        Serial.println(results.value, HEX);
        ir->resume();
      }
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
        Serial.print("CTLIr: ");
        Serial.println(message);      
      }
    }

};

#endif
