#ifndef CTL_LCD_H
#define CTL_LCD_H

#include "Config.h"
#include <ShiftedLCD.h>
#include <SPI.h>
#include <ShiftPinNo.h>

class CTLLcd {

  private:

    int ss_pin;
    boolean enabled=true;

  public:
    LiquidCrystal* lcd; 

     CTLLcd(int _ss_pin){
      ss_pin = _ss_pin;
      lcd=new LiquidCrystal(ss_pin);
    }

     void setup() {
      debug("setup()");
      digitalWrite(ss_pin,HIGH);
      lcd->begin(16, 2);
      lcd->print("Starting system:");
    }


    void printAt(int column,int ligne, char* data){
      lcd->setCursor(column, ligne);
      lcd->print(data);
    }  

    void print(char* data){
      lcd->print(data);
    }  

    void setCursor(int column,int ligne){
      lcd->setCursor(column, ligne);
    }    

    void ping(){
       debug("ping()");
    }
  
    void enable(){
      debug("enabled()");
      enabled=true;
    }

    void disable(){
      debug("disabled()");
      enabled=false;
    }

    void debug(String message){
      if(DEBUG){
        Serial.print("CTLLcd: ");
        Serial.println(message);      
      }
    }

};

#endif
