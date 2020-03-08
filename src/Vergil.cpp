#include <Arduino.h>
#include "Config.h"
#include "CTLProtocol.h"
#include "SNSProtocol.h" 

#include "SNSDht11.h"
#include "SNSDht11Light.h"
#include "SNSMhz19.h"
#include "SNSDigital.h"
#include "CTLVentilo.h" 
#include "CTLHeater.h" 
#include "CTLMainPump.h" 
#include "CTLSwitchPump.h" 
#include "CTLLight.h" 
#include "HUBOut.h"
#include "CTLSd.h"
#include "CTLRtc.h"
#include "CTLIr.h"
#include "COMWifi.h"
#include <LiquidMenu.h>
#include "CTLMenu.h"
#include "Global.h"

LiquidCrystal _lcd(PIN_ARD_LCD_CS);
LiquidMenu    _menu(_lcd);

CTLHeater*      ctlHeater     = new CTLHeater(HUB_ENTRY_HEATER,IDL_TEMPERATURE,MIN_TEMPERATURE,MAX_TEMPERATURE
//,hubOut
); 
CTLVentilo*     ctlVentilo    = new CTLVentilo(HUB_ENTRY_VENTILO_POWER, HUB_ENTRY_VENTILO_DIRECTION
//,hubOut
);
CTLRtc*         ctlRtc        = new CTLRtc();
CTLSd*          ctlSd         = new CTLSd(PIN_ARD_SD_CS);

SNSDht11*       snsDht11      = new SNSDht11(PIN_ARD_SNS_DHT_DATA,ctlHeater,ctlVentilo);

SNSMhz19*       snsMhz        = new SNSMhz19(PIN_ARD_MHZ);

HUBOut*         hubOut        = new HUBOut(PIN_ARD_HUB_OUT_SS_LATCH, HUB_OUT_COUNT,HUB_ENTRY_BUZZER,ctlRtc,snsDht11,snsMhz);
CTLMenu*        ctlMenu       = new CTLMenu(&_lcd,&_menu,hubOut);


CTLMainPump*    ctlMainPump   = new CTLMainPump(HUB_ENTRY_MAIN_PUMP,hubOut);
CTLSwitchPump*  ctlSwitchPump = new CTLSwitchPump(HUB_ENTRY_SWITCH_PUMP,hubOut);
CTLLight*       ctlLight      = new CTLLight(HUB_ENTRY_LIGHT,hubOut);

SNSDigital*     snsDigital    = new SNSDigital(PIN_ARD_SNS_DGT_LOAD,PIN_ARD_SNS_DGT_SCLK,PIN_ARD_SNS_DGT_DATA,ctlMainPump,ctlSwitchPump);

CTLIr*           ctlIr         = new CTLIr(PIN_ARD_IR,ctlMenu,ctlRtc,hubOut);
COMWifi*         comWifi       = new COMWifi(ctlMenu,hubOut);

void debug(String message){
  if(VG_DEBUG){
    Serial.print("Vergil: ");
    Serial.println(message);      
  }
}

void setup(){
  Serial.begin(9600);
  debug("setup()");

  ctlMenu->setup();

  hubOut->setup();

  ctlHeater->setup();
  ctlVentilo->setup();
  ctlMainPump->setup();
  ctlSwitchPump->setup();
  ctlLight->setup();

  snsDht11->setup();
  snsDigital->setup();

  ctlSd->setup();
  ctlRtc->setup();
  ctlIr->setup();

  snsMhz->setup();
  comWifi->setup();
};


void loop(){
    snsDht11->loop();
    ctlMenu->loop();
    hubOut->loop();
    snsDigital->loop();
    ctlIr->loop();
    comWifi->loop();
};