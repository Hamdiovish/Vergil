#ifndef SNSDHT11LIGHT_H
#define SNSDHT11LIGHT_H

#include "Config.h"
#include "SNSProtocol.h"
#include "dht.h"
#include "Global.h"

class SNSDht11Light: public SNSProtocol {

  private:
  
    int data_pin;
    int standByMs=2500;
    uint32_t interval;
    uint32_t latestInterval;
    bool handlingTemperature;
    bool handlingHumidity;

  public:
    dht DHT;

    SNSDht11Light(int _data_pin){
      data_pin = _data_pin;
      interval=INTERVAL_SNS_DHT;
      latestInterval = 0;
      handlingTemperature=false;
      handlingHumidity=false;
    };
   
    double getTemperature(){
      DHT.read11(data_pin);
      return DHT.temperature;
    }
    
    double getHumidity(){
      DHT.read11(data_pin);
      return DHT.humidity;
    }

    void standBy(){
     debug("standBy()");
     delay(standByMs);
    }
    
    void debug(){
      //if(VG_DEBUG){
        Serial.println("");      
     // }
    }    
    
    void debug(String message){
      //if(VG_DEBUG){
        Serial.print("SNSDht11: ");
        Serial.println(message);      
     // }
    }    
    
    void debug(double message){
      //if(VG_DEBUG){
        Serial.print("SNSDht11: ");
        Serial.println(message);      
    //  }
    }

  public:
  
  virtual void setup() {
    }

  virtual void loop(){

    }
////////// END HUMIDITY //////////

};

#endif
