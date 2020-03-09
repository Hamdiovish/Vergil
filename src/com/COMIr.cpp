#include "com/COMIr.h"
#include "utilities/Config.h"
#include "com/COMMenu.h"
#include <IRremote.h>
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

COMIr::COMIr(int _data_pin){
  data_pin=_data_pin;
}

void COMIr::setup() {
  debug("setup()");
  ir=new IRrecv(data_pin);
  ir->enableIRIn();
  //hubOut->lcd->printAt(0,1,"Setup IR done!  ");
}

void COMIr::loop(){
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
          comMenu->up();        
          break;
        };
        //CH
        case 0xFF629D:{
          debug(">>0xFF629D:");
          hubOut->buzz();
          comMenu->ok();        
          break;
        };
        //CH+
        case 0xFFE21D:{
          debug(">>0xFFE21D");
          hubOut->buzz();
          comMenu->down();        
          break;
        };
    }
    Serial.println(results.value, HEX);
    ir->resume();
  }
}

void COMIr::ping(){
    debug("ping()");
}

void COMIr::enable(){
  debug("enabled()");
  enabled=true;
}

void COMIr::disable(){
  debug("disabled()");
  enabled=false;
}

void COMIr::debug(String message){
  //if(VG_DEBUG){
    Serial.print("COMIr: ");
    Serial.println(message);      
  // }
}