#ifndef COMWIFI_H
#define COMWIFI_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <time.h>

#include "utilities/Config.h"
#include "com/COMMenu.h"
#include "controllers/HUBOut.h"
#include "utilities/Injector.h"

class COMWifi {

    private:
        StaticJsonDocument<256> serialData;  
        uint32_t interval;
        uint32_t latestInterval;
        
    public:

        COMWifi();
        void setup();

        void loop();

        void handleReception();

        void handleEmission();
};

#endif