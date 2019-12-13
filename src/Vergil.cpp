#include <Arduino.h>
#include "Config.h"
#include "CTLProtocol.h"
#include "SNSProtocol.h" 

#include "SNSDht11.h"
#include "SNSDigital.h"
#include "CTLVentilo.h" 
#include "CTLHeater.h" 
#include "CTLMainPump.h" 
#include "CTLSwitchPump.h" 
#include "CTLLight.h" 
#include "HUBOut.h"

HUBOut*         hubOut        = new HUBOut(PIN_ARD_HUB_OUT_SS_LATCH, HUB_OUT_COUNT);

CTLHeater*      ctlHeater     = new CTLHeater(HUB_ENTRY_HEATER,IDL_TEMPERATURE,MIN_TEMPERATURE,MAX_TEMPERATURE,hubOut); 
CTLVentilo*     ctlVentilo    = new CTLVentilo(HUB_ENTRY_VENTILO_POWER, HUB_ENTRY_VENTILO_DIRECTION,hubOut);
CTLMainPump*    ctlMainPump   = new CTLMainPump(HUB_ENTRY_MAIN_PUMP,hubOut);
CTLSwitchPump*  ctlSwitchPump = new CTLSwitchPump(HUB_ENTRY_SWITCH_PUMP,hubOut);
CTLLight*       ctlLight      = new CTLLight(HUB_ENTRY_LIGHT,hubOut);

SNSDht11*       snsDht11      = new SNSDht11(PIN_ARD_SNS_DHT_DATA,ctlHeater,ctlVentilo);
SNSDigital*     snsDigital    = new SNSDigital(PIN_ARD_SNS_DGT_LOAD,PIN_ARD_SNS_DGT_SCLK,PIN_ARD_SNS_DGT_DATA,ctlMainPump,ctlSwitchPump);
   
void debug(String message){
  if(DEBUG){
    Serial.print("Vergil: ");
    Serial.println(message);      
  }
}

void setup(){
  Serial.begin(9600);
  debug("setup()");

  hubOut->setup();

  ctlHeater->setup();
  ctlVentilo->setup();
  ctlMainPump->setup();
  ctlSwitchPump->setup();
  ctlLight->setup();

  snsDht11->setup();
  snsDigital->setup();
};


void loop(){
    //snsDht11->loop();
    snsDigital->loop();
};