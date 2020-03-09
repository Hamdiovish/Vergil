#include <Arduino.h>
#include "utilities/Config.h"
#include "protocols/CTLProtocol.h"
#include "protocols/SNSProtocol.h" 

#include "controllers/CTLHeater.h" 
#include "controllers/CTLVentilo.h" 

#include "sensors/SNSDht11.h"
#include "sensors/SNSDht11.h"
#include "sensors/SNSMhz19.h"
#include "sensors/SNSDigital.h"

#include "controllers/CTLMainPump.h" 
#include "controllers/CTLSwitchPump.h" 
#include "controllers/CTLLight.h" 
#include "controllers/HUBOut.h"
#include "controllers/CTLSd.h"
#include "controllers/CTLRtc.h"
#include "controllers/CTLIr.h"
#include "com/COMWifi.h"
#include <LiquidMenu.h>
#include "controllers/CTLMenu.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

LiquidCrystal _lcd(PIN_ARD_LCD_CS);
LiquidMenu    _menu(_lcd);

CTLHeater*      ctlHeater     = new CTLHeater(HUB_ENTRY_HEATER,IDL_TEMPERATURE,MIN_TEMPERATURE,MAX_TEMPERATURE); 
CTLVentilo*     ctlVentilo    = new CTLVentilo(HUB_ENTRY_VENTILO_POWER, HUB_ENTRY_VENTILO_DIRECTION);

SNSDht11*       snsDht11      = new SNSDht11(PIN_ARD_SNS_DHT_DATA);

SNSMhz19*       snsMhz        = new SNSMhz19(PIN_ARD_MHZ);

CTLRtc*         ctlRtc        = new CTLRtc();

CTLSd*          ctlSd         = new CTLSd(PIN_ARD_SD_CS);

HUBOut*         hubOut        = new HUBOut(PIN_ARD_HUB_OUT_SS_LATCH, HUB_OUT_COUNT,HUB_ENTRY_BUZZER);

CTLMenu*        ctlMenu       = new CTLMenu(&_lcd,&_menu);

CTLMainPump*    ctlMainPump   = new CTLMainPump(HUB_ENTRY_MAIN_PUMP);
CTLSwitchPump*  ctlSwitchPump = new CTLSwitchPump(HUB_ENTRY_SWITCH_PUMP);
CTLLight*       ctlLight      = new CTLLight(HUB_ENTRY_LIGHT);

SNSDigital*     snsDigital    = new SNSDigital(PIN_ARD_SNS_DGT_LOAD,PIN_ARD_SNS_DGT_SCLK,PIN_ARD_SNS_DGT_DATA);

CTLIr*           ctlIr         = new CTLIr(PIN_ARD_IR);
COMWifi*         comWifi       = new COMWifi();

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
    ctlMenu->loop();
    snsDigital->loop();
    ctlIr->loop();
    comWifi->loop();
    hubOut->loop();
    snsDht11->loop();
  };