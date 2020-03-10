#include <Arduino.h>
#include <com/COMWifi.h>

#include <ArduinoJson.h>
#include <time.h>

#include "utilities/Config.h"
#include "com/COMMenu.h"
#include "controllers/HUBOut.h"
#include "utilities/Injector.h"


COMWifi::COMWifi(){
    interval=INTERVAL_COM_WIFI_REFRESH_RATE;
    latestInterval=0;
}

void COMWifi::setup(){
    Serial1.begin(115200);
}

void COMWifi::loop(){
    handleReception();

    if (millis() - latestInterval >= interval) {
        latestInterval=millis();
        handleEmission();
  }
}

void COMWifi::handleReception(){
    if (Serial1.available()>0){
        char* t = "/r";
        Serial.println(">>in:");
        String s = Serial1.readStringUntil(*t);
        s.trim();
        Serial.println(s);

        auto error =deserializeJson(serialData, s);
        if (error) {
            Serial.print(F("deserializeJson() failight with code "));
            Serial.println(error.c_str());
            return;
        }

        bool hasTime = serialData.containsKey("time");
        bool hasFan = serialData.containsKey("fan");
        bool hasDirection = serialData.containsKey("direction");
        bool hasHeater = serialData.containsKey("heater");
        bool hasLight = serialData.containsKey("light");
        bool hasInfo = serialData.containsKey("info");

        long timeTime = 0l;
        int stateFan = -1;
        int stateDirection = -1;
        int stateHeater = -1;
        int stateLight = -1;

        if (hasTime){
            Serial.println("has Time:");
            timeTime=serialData["time"];
            Serial.println(timeTime);
            ctlRtc->updateTime(timeTime);
        }

        if(hasFan){
            Serial.println("has Fan");
            stateFan = serialData["fan"];
            if(stateFan==1){
            //relayHeater01State=LOW;
                Serial.println("Heater ON");
            }else if (stateFan==0){
                //relayHeater01State=HIGH;
                Serial.println("Fan OFF");
            }
        }

        if(hasDirection){
            Serial.println("has Direction");
            stateDirection = serialData["direction"];
            if(stateDirection==1){
            //relayHeater01State=LOW;
                Serial.println("Direction ON");
            }else if (stateDirection==0){
                //relayHeater01State=HIGH;
                Serial.println("Direction OFF");
            }
        }
        
        if(hasHeater){
            Serial.println("has Heater");
            stateHeater = serialData["heater"];
            if(stateHeater==1){
            //relayHeater01State=LOW;
                Serial.println("Heater ON");
            }else if (stateHeater==0){
                //relayHeater01State=HIGH;
                Serial.println("Heater OFF");
            }
        } 

        if (hasLight){
            Serial.println("has Light");
            stateLight = serialData["light"];
            if(stateLight==1){
                //relayLight01State=LOW;
                Serial.println("Light ON");
            }else if (stateLight==0){
                //relayLight01State=HIGH;
                Serial.println("Light OFF");
            }
        }

        if (hasInfo){
            Serial.println("has Info");
            const char* stateInfo = serialData["info"];
            Serial.println(String(stateInfo));
        }
    }
}

void COMWifi::handleEmission(){
    long time;
    double temperature;
    double humidity;
    double co2;

    time = ctlRtc->getTimestamp();
    temperature=snsDht11->getTemperature();
    humidity=snsDht11->getHumidity();
    co2 = snsMhz->getCo2();

    JsonObject root = serialData.to<JsonObject>();
    root["time"] = String(time);
    root["temperature"] = String(temperature);
    root["humidity"] = String(humidity);
    root["co2"] = String(co2);
    serializeJsonPretty(root, Serial1);
}