#ifndef CTL_MENU_H
#define CTL_MENU_H

#include "Config.h"
#include <LiquidMenu.h>

class CTLMenu{

  private:

    int ss_pin;
    boolean enabled=true;
    boolean defaultScreenShowed=true;
    long lastMs_nextScreen=0;
    long period_nextScreen=3000;

  public:
    LiquidCrystal* lcd; 
    LiquidMenu* menu;
    LiquidScreen* welcome_screen;
    LiquidScreen* data_screen;

    LiquidLine* welcome_line_1;
    LiquidLine* welcome_line_2;

    LiquidLine* data_line_1;
    LiquidLine* data_line_2;

    char* line1="Data title";
    char* line2="Data value";

     CTLMenu(LiquidCrystal* _lcd,LiquidMenu* _menu){
      lcd=_lcd;
      menu=_menu;
    }

     void setup() {
      debug("setup()");
      digitalWrite(ss_pin,HIGH);

      welcome_line_1 = new  LiquidLine(0, 0, "  VERGIL FARM   ");
      welcome_line_2 = new  LiquidLine(0, 1, "     Hello      ");
      welcome_screen = new  LiquidScreen(*welcome_line_1, *welcome_line_2);

      data_line_1 = new  LiquidLine(0, 0,line1);
      data_line_2 = new  LiquidLine(0, 1,line2);

      data_screen = new LiquidScreen(*data_line_1,*data_line_2);

      lcd->begin(16, 2);

      menu->add_screen(*welcome_screen);
      menu->add_screen(*data_screen);
      menu->change_screen(welcome_screen);
      menu->update();
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
        Serial.print("CTLMenu: ");
        Serial.println(message);      
      }
    }

    void updateDisplay(char* l1, char* l2){
      line1=l1;
      line2=l2;
      menu->change_screen(data_screen);
      menu->update();
      defaultScreenShowed=false;
      lastMs_nextScreen=millis();
    }

    void loop(){
      if(defaultScreenShowed==false){
          // Periodic switching to the next screen.
        if (millis() - lastMs_nextScreen > period_nextScreen) {
          lastMs_nextScreen = millis();
          menu->change_screen(welcome_screen);
          menu->update();
          defaultScreenShowed=true;
        }
      }
    }

};

#endif
