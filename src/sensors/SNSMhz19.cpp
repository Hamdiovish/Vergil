#include "sensors/SNSMhz19.h"

#include "utilities/Config.h"
#include "protocols/SNSProtocol.h"
#include "dht.h"
#include "utilities/Global.h"

SNSMhz19::SNSMhz19(int _data_pin){
  data_pin = _data_pin;
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

unsigned long SNSMhz19::getCo2(){
  unsigned th,tl,ppm=0;
    do {
      th = pulseIn(data_pin, HIGH, 1004000) / 1000;
      tl = 1004 - th;
      ppm = 2000 * (th-2)/(th+tl-4);
    } while (th == 0);
    return ppm;
}

void SNSMhz19::setup() {
  pinMode(data_pin, INPUT);
}

void SNSMhz19::loop(){

}
////////// END HUMIDITY //////////

