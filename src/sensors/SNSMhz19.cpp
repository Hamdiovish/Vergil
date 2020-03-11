#include "sensors/SNSMhz19.h"
#include <SoftwareSerial.h>  
#include "MHZ19.h"            

#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "dht.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

SNSMhz19::SNSMhz19(MHZ19* _mhz){
  mhz=_mhz;
  interval=INTERVAL_SNS_MHZ;
  latestInterval = 0;
  handlingTemperature=false;
  handlingHumidity=false;
};

void SNSMhz19::standBy(){
  debug("standBy()");
  delay(standByMs);
}

void SNSMhz19::debug(){
  //if(VG_DEBUG){
    Serial.println("");      
  //}
}    

void SNSMhz19::debug(String message){
  //if(VG_DEBUG){
    Serial.print("SNSMhz19: ");
    Serial.println(message);      
//  }
}    

void SNSMhz19::debug(double message){
  //if(VG_DEBUG){
    Serial.print("SNSMhz19: ");
    Serial.println(message);      
  // }
}

int SNSMhz19::getCo2(){
  return mhz->getCO2();                             // Request CO2 (as ppm)
}

void SNSMhz19::setup() {
    _sSerialMhz.begin(MHZ_UART_BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    mhz->begin(_sSerialMhz);                                // *Serial(Stream) refence must be passed to library begin(). 
    mhz->autoCalibration(false);  
    getDeviceInfo();
}

void SNSMhz19::getDeviceInfo() {

  char myVersion[4];          
  mhz->getVersion(myVersion);

  Serial.print("\nFirmware Version: ");
  for(byte i = 0; i < 4; i++)
  {
    Serial.print(myVersion[i]);
    if(i == 1)
      Serial.print(".");    
  }
   Serial.println("");

   Serial.print("Range: ");
   Serial.println(mhz->getRange());   
   Serial.print("Background CO2: ");
   Serial.println(mhz->getBackgroundCO2());
   Serial.print("Temperature Cal: ");
   Serial.println(mhz->getTempAdjustment());
}

void SNSMhz19::loop(){

}
////////// END HUMIDITY //////////

