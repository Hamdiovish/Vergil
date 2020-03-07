#ifndef CTL_RTC_H
#define CTL_RTC_H

#include "Config.h"
#include <DS3232RTC.h>
#include "CTLLcd.h"

class CTLRtc {

  private:

    DS3232RTC*  rtc;
    CTLLcd* lcd; 
    boolean enabled=true;

  public:

    CTLRtc(CTLLcd* _lcd){
      rtc=new DS3232RTC();
      lcd=_lcd;
    }

    void setup() {
      debug("setup()");
      rtc->begin();
      lcd->printAt(0,1,"Setup RTC done!");
      //rtc->set((time_t)1583544247);
      String ts = String(getTimestamp());
      debug(ts);
    }

//  printf("%jd seconds since the epoch began\n", (intmax_t)epoch);
//    printf("%s", asctime(gmtime(&epoch)));
  
    long getTimestamp(){
      debug("getTimestamp()");
      time_t t = rtc->get();
      char buf[40];
      sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
      debug(buf);
      return long(t);
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
