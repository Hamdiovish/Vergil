#ifndef CTL_RTC_H
#define CTL_RTC_H

#include "utilities/Config.h"
#include <DS3232RTC.h>
#include "utilities/Global.h"

class CTLRtc {

  private:

    DS3232RTC*  rtc;
    boolean enabled=true;

  public:

    CTLRtc();

    void setup();

//  printf("%jd seconds since the epoch began\n", (intmax_t)epoch);
//    printf("%s", asctime(gmtime(&epoch)));
  
    void updateTime(long time);

    long getTimestamp();

    void getTimeFormatted(char* result);

    String getTimeFormattedString();

    void ping();
  
    void enable();

    void disable();

    void debug(String message);

    void debug(long message);

};

#endif
