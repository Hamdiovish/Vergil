#ifndef HUB_OUT_H
#define HUB_OUT_H

#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "controllers/CTLRtc.h"

#include <SPI.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
#include "sensors/SNSMhz19.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

class HUBOut {

  private:
  
    int ss_latch_pin;
    int count_pin;
    shiftOutX* sr; 

    int buzzer_pin;
    boolean buzzing=false;
    uint32_t buzzerInterval;
    uint32_t buzzerLatestInterval;

  public:
  
    HUBOut(){

    }

    HUBOut(int _ss_latch_pin, int _count_pin, int _buzzer_pin);
    
  virtual void setup();
  
  void on(int pin);

  void off(int pin);

  void allOff();

  void allOn();

    
  void onRelay(int pin);

  void offRelay(int pin);

  void allOffRelay();

  void allOnRelay();

  uint8_t getState(int pin);

  void debug(String message);

  void treatBuzzer();

  void buzz();

  void updateTime(long time);
  
  void displayTime(char* data);

  void loop();

};

#endif
