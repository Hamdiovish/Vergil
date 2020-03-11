#ifndef SNSDALLAS_H
#define SNSDALLAS_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "controllers/CTLVentilo.h" 
#include "controllers/CTLHeater.h"
#include "utilities/Injector.h"


class SNSDallas: public SNSProtocol {

  private:
  
    int data_pin;
    int standByMs=2500;
    dht DHT;
    uint32_t interval;
    uint32_t latestInterval;
    bool handlingTemperature;
    bool handlingHumidity;
    DallasTemperature* dallas;

  public:

  SNSDallas(DallasTemperature* _dallas);
  
  float getTemperature();
  
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
