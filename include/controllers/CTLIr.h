#ifndef CTL_IR_H
#define CTL_IR_H

#include "utilities/Config.h"
#include "controllers/CTLMenu.h"
#include <IRremote.h>
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"

class CTLIr {

  private:

    boolean enabled=true;
    int data_pin;
    IRrecv* ir;
    decode_results results;

    
  public:

    CTLIr(int _data_pin);

    void setup();

    void loop();

    void ping();
  
    void enable();

    void disable();

    void debug(String message);

};

#endif
