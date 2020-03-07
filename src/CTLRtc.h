#ifndef CTL_RTC_H
#define CTL_RTC_H

#include "Config.h"
#include <DS3232RTC.h>

class CTLRtc {

  private:

    DS3232RTC*  rtc;
    boolean enabled=true;

  public:

    CTLRtc(){
      rtc=new DS3232RTC();
    }

    void setup() {
      debug("setup()");
      rtc->begin();
      debug(getTimeFormattedString());
    }

//  printf("%jd seconds since the epoch began\n", (intmax_t)epoch);
//    printf("%s", asctime(gmtime(&epoch)));
  
    void updateTime(long time){
        debug("updateTime()");
        rtc->set((time_t)time);
        debug(getTimeFormatted());
    }

    long getTimestamp(){
      debug("getTimestamp()");
      time_t t = rtc->get();
      return long(t);
    }

    char* getTimeFormatted(){
      debug("getTimeFormatted()");
      time_t t = rtc->get();
      char buf[40];
      sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
      return buf;
    }

    String getTimeFormattedString(){
      debug("getTimeFormattedString()");
      time_t t = rtc->get();
      char buf[40];
      sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
      String s=buf;
      return s;
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
