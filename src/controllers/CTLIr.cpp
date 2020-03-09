#include "controllers/CTLIr.h"
#include "utilities/Config.h"
#include "controllers/CTLMenu.h"
#include <IRremote.h>
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

CTLIr::CTLIr(int _data_pin){
  data_pin=_data_pin;
}

void CTLIr::setup() {
  debug("setup()");
  ir=new IRrecv(data_pin);
  ir->enableIRIn();
  //hubOut->lcd->printAt(0,1,"Setup IR done!  ");
}

void CTLIr::loop(){
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

void CTLIr::ping(){
    debug("ping()");
}

void CTLIr::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLIr::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLIr::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTLIr: ");
    Serial.println(message);      
  // }
}