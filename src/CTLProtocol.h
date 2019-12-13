#ifndef CTLPROTOCOL_H
#define CTLPROTOCOL_H

#include "HUBOut.h"
 
class CTLProtocol {
public:
   virtual void on();  // Needs to be implemented by each subclass
   virtual void off();
   virtual void setup();
   virtual void ping();
};

#endif
