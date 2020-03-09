#include <com/COMWifi.h>

#include <ArduinoJson.h>
#include <time.h>

#include "utilities/Config.h"
#include "controllers/CTLMenu.h"
#include "controllers/HUBOut.h"
#include "utilities/Injector.h"


COMWifi::COMWifi(){
}

void COMWifi::setup(){
    Serial1.begin(115200);
}

void COMWifi::loop(){
    if (Serial1.available()>0){
        char* t = "/r";
        Serial.println(">>in:");
        String s = Serial1.readStringUntil(*t);   // Until CR (Carriage Return)
        s.trim();
        Serial.println(s);

        auto error =deserializeJson(serialData, s);
        if (error) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return;
        }
        bool hasFan = serialData.containsKey("fan");
        bool hasLed = serialData.containsKey("led");
        bool hasNow = serialData.containsKey("time");
        int stateFan = -1;
        int stateLed = -1;
        long timeNow = 0l;

        if (hasNow){
            Serial.println("has Now:");
            timeNow=serialData["time"];
            Serial.println(timeNow);
            ctlRtc->updateTime(timeNow);
        }
        
        if(hasFan){
            Serial.println("has Fan");
            stateFan = serialData["fan"];
            if(stateFan==1){
            //relayFan01State=LOW;
            //digitalWrite(relayFan01, relayFan01State);
                Serial.println("Fan ON");
            }else if (stateFan==0){
                //relayFan01State=HIGH;
                //digitalWrite(relayFan01, relayFan01State);              
                Serial.println("Fan OFF");
            }
        }
        
        if (hasLed){
            Serial.println("has Led");
            stateLed = serialData["led"];
            if(stateLed==1){
                //relayLed01State=LOW;
                //digitalWrite(relayLed01, relayLed01State);
                Serial.println("Led ON");
            }else if (stateLed==0){
                //relayLed01State=HIGH;
                //digitalWrite(relayLed01, relayLed01State);              
                Serial.println("Led OFF");
            }
        }
    }
}
