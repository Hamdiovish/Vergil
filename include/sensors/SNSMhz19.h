#ifndef SNSMhz19LIGHT_H
#define SNSMhz19LIGHT_H

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

  public:

  SNSMhz19(int _data_pin);;

  void standBy();
  
  void debug();    
  
  void debug(String message);    
  
  void debug(double message);

  unsigned long getCo2();

  virtual void setup() ;

  virtual void loop();
////////// END HUMIDITY //////////

};

#endif
