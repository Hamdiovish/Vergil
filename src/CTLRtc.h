#ifndef CTL_RTC_H
#define CTL_RTC_H

#include "Config.h"
#include <DS3231.h>
#include "CTLLcd.h"

class CTLRtc {

  private:

    DS3231*  rtc;
    CTLLcd* lcd; 
    boolean enabled=true;

  public:

    CTLRtc(CTLLcd* _lcd){
      rtc=new DS3231(SDA, SCL);
      lcd=_lcd;
    }

    void setup() {
      debug("setup()");
      rtc->begin();
      lcd->printAt(0,1,"Setup RTC done!");
      String ts = String(getTimestamp());
      debug(ts);
    }

    long getTimestamp(){
      debug("getTimestamp()");
      return rtc->getUnixTime(rtc->getTime());
    }

    void ping(){
       debug("ping()");
    }
  
    void enable(){
      debug("enabled()");
      enabled=true;
    }

    void disable(){
      debug("disabled()");
      enabled=false;
    }

    void debug(String message){
      if(DEBUG){
        Serial.print("CTLRtc: ");
        Serial.println(message);      
      }
    }

    void debug(long message){
      if(DEBUG){
        Serial.print("CTLRtc long: ");
        Serial.println(message);      
      }
    }

};

#endif
