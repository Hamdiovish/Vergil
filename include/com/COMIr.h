#ifndef CTL_IR_H
#define CTL_IR_H

#include "utilities/Config.h"
#include "com/COMMenu.h"
#include <IRremote.h>
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

class COMIr {

  private:

    boolean enabled=true;
    int data_pin;
    IRrecv* ir;
    decode_results results;

    
  public:

    COMIr(int _data_pin);

    void setup();

    void loop();

    void ping();
  
    void enable();

    void disable();

    void debug(String message);

};

#endif
