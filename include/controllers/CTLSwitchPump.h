#ifndef CTL_SWITCH_PUMP_H
#define CTL_SWITCH_PUMP_H

#include "utilities/Config.h"
#include "sensors/SNSDht11.h"
#include "protocols/CTLProtocol.h"
#include "controllers/HUBOut.h"
#include "utilities/Global.h"
 
class CTLSwitchPump: public CTLProtocol {

  private:

    int power_pin;
    boolean enabled=true;

  public:

     CTLSwitchPump(int _power_pin);

    virtual void setup() ;

    virtual void on();
    
    virtual void off();

    virtual void ping();
  
    void enable();

    void disable();

    void debug(String message);
    
    void debug(double message);

};

#endif
