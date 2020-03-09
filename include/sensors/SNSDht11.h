#ifndef SNSDHT11_H
#define SNSDHT11_H

#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "dht.h"
#include "controllers/CTLVentilo.h" 
#include "controllers/CTLHeater.h"
#include "utilities/Injector.h"


class SNSDht11: public SNSProtocol {

  private:
  
    int data_pin;
    int standByMs=2500;
    dht DHT;
    uint32_t interval;
    uint32_t latestInterval;
    bool handlingTemperature;
    bool handlingHumidity;

  public:

  SNSDht11(int _data_pin);
  
  double getTemperature();
  
  double getHumidity();

  void standBy();
  
  void debug();    
  
  void debug(String message);    
  
  void debug(double message);

  public:
  
  virtual void setup() ;

  virtual void loop();

////////// START TEMPERATURE //////////

  void crashTemperature(double temperature);
  
  void decreaseTemperature();
    
  void increaseTemperature();

  void handleTemperature(double temperature);
////////// END TEMPERATURE //////////

////////// START HUMIDITY //////////

  void crashHumidity(double humidity);
  void decreaseHumidity();
  void increaseHumidity();
    
  void handleHumidity(double humidity);
  ////////// END HUMIDITY //////////

};

#endif
