#include <Arduino.h>
#include <IRremote.h>
#include <ArduinoJson.h>
//#include "SoftwareSerial.h"
#include <time.h>

StaticJsonDocument<200> serialData;

const int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

int relayFan01 = 8;
int relayLed01 = 9;
volatile byte relayFan01State = HIGH;
volatile byte relayLed01State = HIGH;

//SoftwareSerial Serial1(6, 7); // RX, TX
const char* endLine="#";

void _setup(){
  Serial1.begin(9600);
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  digitalWrite(relayFan01, HIGH);
  digitalWrite(relayLed01, HIGH);

  pinMode(relayFan01, OUTPUT);
  digitalWrite(relayFan01, HIGH);
  pinMode(relayLed01, OUTPUT);
  digitalWrite(relayLed01, HIGH);
}

void irBusiness(){
    if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        switch(results.value){
            case 0x90FD718E: //Recep button "1"
            case 0xFF30CF: //Keypad button "1"
            case 0xFFF807:
            if(relayFan01State==HIGH){
              relayFan01State=LOW;
              digitalWrite(relayFan01, relayFan01State);
              }
              else{
              relayFan01State=HIGH;
              digitalWrite(relayFan01, relayFan01State);              
              }
            break;
            case 0x90FD619E: //Recep button "2"
            case 0xFF18E7: //Keypad button "2"
            case 0xFFDA25:
            if(relayLed01State==HIGH){
              relayLed01State=LOW;
              digitalWrite(relayLed01, relayLed01State);
              }
              else{
              relayLed01State=HIGH;
              digitalWrite(relayLed01, relayLed01State);              
              }     
            break;     
              
            delay(2000);
        }
        irrecv.resume();
  }
}

void espBusiness(){
 if (Serial1.available()>0)
    {
       String s = Serial1.readStringUntil(endLine);   // Until CR (Carriage Return)
       s.replace("#", "");

      deserializeJson(serialData, s);

      bool hasFan = serialData.containsKey("fan");
      bool hasLed = serialData.containsKey("led");
      bool hasNow = serialData.containsKey("time");
      int stateFan = -1;
      int stateLed = -1;
      long timeNow = 0l;

      if (hasNow){
          Serial.println("has Now:");
          timeNow=serialData["time"];
          timeNow-= UNIX_OFFSET;
          Serial.println(timeNow);
          Serial.println(ctime(&timeNow));
      }
      
      if(hasFan){
       Serial.println("has Fan");
       stateFan = serialData["fan"];
       if(stateFan==1){
          relayFan01State=LOW;
          digitalWrite(relayFan01, relayFan01State);
          Serial.println("Fan ON");
        }
        else if (stateFan==0){
          relayFan01State=HIGH;
          digitalWrite(relayFan01, relayFan01State);              
          Serial.println("Fan OFF");
       }
     }
     
     if (hasLed){
      Serial.println("has Led");
      stateLed = serialData["led"];
      if(stateLed==1){
        relayLed01State=LOW;
        digitalWrite(relayLed01, relayLed01State);
        Serial.println("Led ON");
      }
      else if (stateLed==0){
        relayLed01State=HIGH;
        digitalWrite(relayLed01, relayLed01State);              
        Serial.println("Led OFF");
     }
    }
  }
}
  
void _loop(){
  irBusiness();
  espBusiness();
}