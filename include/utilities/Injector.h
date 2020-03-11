#include "Arduino.h"

#include "controllers/HUBOut.h"
#include "controllers/CTLHeater.h"
#include "controllers/CTLVentilo.h"
#include "sensors/SNSMhz19.h"
#include "controllers/CTLRtc.h"
#include "com/COMMenu.h"
#include "controllers/CTLMainPump.h"
#include "controllers/CTLSwitchPump.h"
#include "controllers/CTLLight.h"
#include "com/COMIr.h"
#include "com/COMWifi.h"
#include "sensors/SNSDallas.h"

extern class HUBOut*         hubOut;
extern class CTLHeater*      ctlHeater;
extern class CTLVentilo*     ctlVentilo;
extern class SNSDht11*       snsDht11;
extern class SNSMhz19*       snsMhz;
extern class CTLRtc*         ctlRtc ;
extern class CTLSd*          ctlSd ;
extern class COMMenu*        comMenu;
extern class CTLMainPump*    ctlMainPump;
extern class CTLSwitchPump*  ctlSwitchPump;
extern class CTLLight*       ctlLight;
extern class SNSDigital*     snsDigital;
extern class COMIr*          comIr;
extern class COMWifi*        comWifi;
extern class SoftwareSerial _sSerialMhz;
extern class SNSDallas*      snsDallas;