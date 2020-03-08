#ifndef CTL_IR_H
#define CTL_IR_H

#include "Config.h"
#include "CTLMenu.h"
#include <IRremote.h>
#include "HUBOut.h"
#include "Global.h"
#include "Injector.h"

class CTLIr {

  private:

    boolean enabled=true;
    int data_pin;
    IRrecv* ir;
    decode_results results;

    
  public:

    CTLIr(int _data_pin){
      data_pin=_data_pin;
    }

    void setup() {
      debug("setup()");
      ir=new IRrecv(data_pin);
      ir->enableIRIn();
      //hubOut->lcd->printAt(0,1,"Setup IR done!  ");
    }

    void loop(){
      if (ir->decode(&results)){
        switch(results.value){
          //Recep button FFC23D "Stop/Resume"
          case 0xFFC23D:{
            debug(">>0xFFC23D:");
            hubOut->buzz();
            if(VG_SERIAL_ENABLED){
                VG_SERIAL_ENABLED=false;
                Serial.end();
              }else{
                VG_SERIAL_ENABLED=true;
                Serial.begin(9600);
              }
            break;
            };
            //EQ
            case 0xFF906F:{
              debug(">>0xFF906F:");
              hubOut->buzz();
              ctlMenu->updateDisplayTmp();        
              break;
            };
            //CH-
            case 0xFFA25D:{ 
              debug(">>0xFFA25D:");
              hubOut->buzz();
              ctlMenu->up();        
              break;
            };
            //CH
            case 0xFF629D:{
              debug(">>0xFF629D:");
              hubOut->buzz();
              ctlMenu->ok();        
              break;
            };
            //CH+
            case 0xFFE21D:{
              debug(">>0xFFE21D");
              hubOut->buzz();
              ctlMenu->down();        
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
      //if(VG_DEBUG){
        Serial.print("CTLIr: ");
        Serial.println(message);      
     // }
    }

};

#endif
