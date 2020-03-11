#ifndef SNSMhz19LIGHT_H
#define SNSMhz19LIGHT_H
                            
#include <SoftwareSerial.h>  
#include "MHZ19.h"            
#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "dht.h"
#include "utilities/Global.h"

class SNSMhz19: public SNSProtocol {

  private:
  
    int data_pin;
    int standByMs=2500;
    uint32_t interval;
    uint32_t latestInterval;
    bool handlingTemperature;
    bool handlingHumidity;
    MHZ19* mhz;
  
  public:

  SNSMhz19(MHZ19* _mhz);

  void standBy();
  
  void debug();    
  
  void debug(String message);    
  
  void debug(double message);

  int getCo2();
  
  void getDeviceInfo();

  virtual void setup() ;

  virtual void loop();
////////// END HUMIDITY //////////

};

#endif
