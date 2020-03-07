#ifndef CTL_IR_H
#define CTL_IR_H

#include "Config.h"
#include "CTLLcd.h"
#include <IRremote.h>
#include "HUBOut.h"

class CTLIr {

  private:

    CTLLcd* lcd; 
    boolean enabled=true;
    int data_pin;
    IRrecv* ir;
    decode_results results;
    HUBOut* hubOut;
  
  public:

    CTLIr(int _data_pin,CTLLcd* _lcd,HUBOut* _hubOut){
      data_pin=_data_pin;
      lcd=_lcd;
      hubOut=_hubOut;
    }

    void setup() {
      debug("setup()");
      ir=new IRrecv(data_pin);
      ir->enableIRIn();
      lcd->printAt(0,1,"Setup IR done!  ");
    }

    void loop(){
      if (ir->decode(&results)){
        hubOut->buzz();
        switch(results.value){
          case 0xFFC23D:{ //Recep button FFC23D "Stop/Resume"
            if(SERIAL_ENABLED){
                SERIAL_ENABLED=false;
                Serial.end();
              }else{
                SERIAL_ENABLED=true;
                Serial.begin(9600);
              }
            }
            break;
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
