#ifndef SNSMhz19LIGHT_H
#define SNSMhz19LIGHT_H

#include "Config.h"
#include "SNSProtocol.h"
#include "dht.h"

class SNSMhz19: public SNSProtocol {

  private:
  
    int data_pin;
    int standByMs=2500;
    uint32_t interval;
    uint32_t latestInterval;
    bool handlingTemperature;
    bool handlingHumidity;

  public:

    SNSMhz19(int _data_pin){
      data_pin = _data_pin;
      interval=INTERVAL_SNS_MHZ;
      latestInterval = 0;
      handlingTemperature=false;
      handlingHumidity=false;
    };

    void standBy(){
     debug("standBy()");
     delay(standByMs);
    }
    
    void debug(){
      if(DEBUG){
        Serial.println("");      
      }
    }    
    
    void debug(String message){
      if(DEBUG){
        Serial.print("SNSMhz19: ");
        Serial.println(message);      
      }
    }    
    
    void debug(double message){
      if(DEBUG){
        Serial.print("SNSMhz19: ");
        Serial.println(message);      
      }
    }

    unsigned long getCo2(){
      unsigned long th,tl,ppm=0;
        do {
          th = pulseIn(data_pin, HIGH, 1004000) / 1000;
          tl = 1004 - th;
          ppm = 2000 * (th-2)/(th+tl-4);
        } while (th == 0);
        return ppm;
    }

  virtual void setup() {
      pinMode(data_pin, INPUT);
    }

  virtual void loop(){

    }
////////// END HUMIDITY //////////

};

#endif
