#ifndef SNS_DIGITAL_H
#define SNS_DIGITAL_H

#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "controllers/CTLMainPump.h"
#include "controllers/CTLSwitchPump.h"
#include "controllers/CTLHeater.h"
#include "controllers/CTLVentilo.h"
#include "controllers/CTLLight.h"

#include <ShiftIn.h>
#include "utilities/Global.h"
#include "utilities/Injector.h"

class SNSDigital: public SNSProtocol{

  private:
  
    int load_pin;
    int data_pin;
    int clock_pin;

    uint32_t interval;
    uint32_t latestInterval;

    ShiftIn<1> shift;

  public:

  SNSDigital(int _load_pin,int _clock_pin,int _data_pin);;
    
  virtual void setup() ;
  
  
  virtual void loop() ;
    
  void handleUpdates() ;

  void debug(String message);
  
  void debugBoolean(boolean message);
};

#endif
//https://infectedbytes.com/2016/07/arduino-shiftin.html