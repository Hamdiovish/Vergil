#include "utilities/Config.h"
#include "sensors/SNSDallas.h"
#include "protocols/SNSProtocol.h"
#include "controllers/CTLVentilo.h" 
#include "controllers/CTLHeater.h"
#include "utilities/Injector.h"


  SNSDallas::SNSDallas(DallasTemperature* _dallas){
    dallas = _dallas;
    interval=INTERVAL_SNS_DHT;
    latestInterval = 0;
    handlingTemperature=false;
    handlingHumidity=false;
  };
  
  float SNSDallas::getTemperature(){
    dallas->requestTemperatures(); 
    return dallas->getTempCByIndex(0);
  }

  void SNSDallas::standBy(){
    debug("standBy()");
    delay(standByMs);
  }
  
  void SNSDallas::debug(){
    //if(VG_DEBUG){
      Serial.println("");      
    // }
  }    
  
  void SNSDallas::debug(String message){
    //if(VG_DEBUG){
      Serial.print("SNSDallas: ");
      Serial.println(message);      
    // }
  }    
  
  void SNSDallas::debug(double message){
    //if(VG_DEBUG){
      Serial.print("SNSDallas: ");
      Serial.println(message);      
    //}
  }


   void SNSDallas::setup() {
       dallas->begin();
  }

 void SNSDallas::loop(){
  }