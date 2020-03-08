#ifndef SNSDHT11_H
#define SNSDHT11_H

#include "Config.h"
#include "SNSProtocol.h"
#include "dht.h"
#include "CTLVentilo.h" 
#include "CTLHeater.h"
#include "Injector.h"


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

    SNSDht11(int _data_pin){
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
      //}
    }

  public:
  
   virtual void setup() {
    }

  virtual void loop(){
    if (millis() - latestInterval >= interval) {
        latestInterval=millis();
        DHT.read11(data_pin);
        //String t_unit="C";
        //String h_unit="%";
        //String display=DHT.temperature+t_unit+" - "+DHT.humidity+h_unit;
        //char* dislayStr="";
        //strcpy(dislayStr, display.c_str()); 
        //lcd->printAt(0,1,dislayStr);
        handleTemperature(DHT.temperature);
        handleHumidity(DHT.humidity);
      }
    }

////////// START TEMPERATURE //////////

   void crashTemperature(double temperature){
    debug("crashTemperature()");
    if(temperature<CRASH_MIN_TEMPERATURE){
     debug("CRASH_MIN_TEMPERATURE");  
    }else if (temperature>CRASH_MAX_TEMPERATURE){
     debug("CRASH_MAX_TEMPERATURE");  
    }
  }
  
  void decreaseTemperature(){
     debug("reduceTemperature");
     ctlHeater->off();
  }
    
  void increaseTemperature(){
     debug("increaseTemperature");
     ctlHeater->on();
  }

  void handleTemperature(double temperature){
    debug(">>temperature!");
    String tmpStr=String(temperature);
    debug(tmpStr);

    if(temperature<=CRASH_MIN_TEMPERATURE||temperature>=CRASH_MAX_TEMPERATURE){
      crashTemperature(temperature);
      return;
    }

    if(handlingTemperature){
      if(
        (temperature>=(IDL_TEMPERATURE-IDL_TEMPERATURE_INTERVAL))&&
        (temperature<=(IDL_TEMPERATURE+IDL_TEMPERATURE_INTERVAL))
        ){
            debug(">>executing:");
            handlingTemperature=false;
            ctlHeater->off();
            ctlVentilo->off();
            debug("Temperature is finished handling...");
            return;
          }else{
            debug("Temperature is being handling...");
            return;
          }     
      }
      
    if(temperature<MIN_TEMPERATURE){
      handlingTemperature=true;
      increaseTemperature();
    }
    else if(temperature>MAX_TEMPERATURE){
      handlingTemperature=true;
      decreaseTemperature();
      }
    else if(temperature==IDL_TEMPERATURE){
      debug("Temperature is ideal...");
      }
    else{
      debug("handleTemperature(): IDLE");
      }
    }

////////// END TEMPERATURE //////////

////////// START HUMIDITY //////////

   void crashHumidity(double humidity){
    debug("crashHumidity()");
    if(humidity<CRASH_MIN_TEMPERATURE){
     debug("CRASH_MIN_HUMDITY");  
    }else if (humidity>CRASH_MAX_TEMPERATURE){
     debug("CRASH_MAX_HUMDITY");  
    }
  }
  void decreaseHumidity(){
     debug("reduceHumidity()");
     ctlVentilo->clockWise();
    }
  void increaseHumidity(){
     debug("increaseHumidity()");
     ctlVentilo->antiClockWise();
    }
    
  void handleHumidity(double humidity){
    debug(">>humidity:");
    debug(humidity);

    if(humidity<=CRASH_MIN_HUMIDITY||humidity>=CRASH_MAX_HUMIDITY){
      crashHumidity(humidity);
      return;
    }

    if(handlingHumidity){
      if(
        (humidity>=(IDL_HUMIDITY-IDL_HUMIDITY_INTERVAL))&&
        (humidity<=(IDL_HUMIDITY+IDL_HUMIDITY_INTERVAL))
        ){
          debug(">>executing:");
          handlingHumidity=false;
          ctlHeater->off();
          ctlVentilo->off();
          debug("Humidity is finished handling...");
          return;
        }else{
          debug("Humidity is being handling...");
          return;
        }     
      }
      
    if(humidity<MIN_HUMIDITY){
      handlingHumidity=true;
      increaseHumidity();
      }
    else if(humidity>MAX_HUMIDITY){
      handlingHumidity=true;
      decreaseHumidity();
      }
    else if(humidity==IDL_HUMIDITY){
      debug("Humidity is ideal...");
      }
    else{
      debug("handleHumidity(): IDLE");
      }
      return;
    }


////////// END HUMIDITY //////////

};

#endif
