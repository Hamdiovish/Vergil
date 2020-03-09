#include "controllers/CTLRtc.h"
#include "utilities/Config.h"
#include <DS3232RTC.h>
#include "utilities/Global.h"


CTLRtc::CTLRtc(){
  rtc=new DS3232RTC();
}

void CTLRtc::setup() {
  debug("setup()");
  rtc->begin();
  //debug(getTimeFormattedString());
}

//  printf("%jd seconds since the epoch began\n", (intmax_t)epoch);
//    printf("%s", asctime(gmtime(&epoch)));

void CTLRtc::updateTime(long time){
    debug("updateTime()");
    rtc->set((time_t)time);
    //debug(getTimeFormatted());
}

long CTLRtc::getTimestamp(){
  debug("getTimestamp()");
  time_t t = rtc->get();
  return long(t);
}

void CTLRtc::getTimeFormatted(char* result){
  debug("getTimeFormatted()");
  time_t t = rtc->get();
  char buf[40];
  sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
    hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
  strcpy(result,buf);
}

String CTLRtc::getTimeFormattedString(){
  debug("getTimeFormattedString()");
  time_t t = rtc->get();
  char buf[40];
  sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
    hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
  String s=buf;
  return s;
}

void CTLRtc::ping(){
    debug("ping()");
}

void CTLRtc::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLRtc::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLRtc::debug(String message){
  //if(VG_DEBUG){
    Serial.print("CTLRtc: ");
    Serial.println(message);      
  // }
}

void CTLRtc::debug(long message){
  //if(VG_DEBUG){
    Serial.print("CTLRtc long: ");
    Serial.println(message);      
  // }
}

