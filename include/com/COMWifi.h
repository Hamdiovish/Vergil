#ifndef COMWIFI_H
#define COMWIFI_H

#include <ArduinoJson.h>
#include <time.h>

#include "utilities/Config.h"
#include "controllers/CTLMenu.h"
#include "controllers/HUBOut.h"
#include "utilities/Injector.h"

class COMWifi {

    private:
        StaticJsonDocument<200> serialData;
  
    public:

        COMWifi();
        void setup();

        void loop();
};

#endif