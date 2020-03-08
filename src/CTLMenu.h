#ifndef CTL_MENU_H
#define CTL_MENU_H

#include <LiquidMenu.h>
#include "HUBOut.h"
#include "SNSDht11.h"
#include "Config.h"
#include "Global.h"

void blankFunction();

void selectedCo2();

void selectedHumidity();

void selectedTemperature();

void selectedTime();

void selectedGoSensors();

void selectedGoWelcome();

void selectedGoMain();

class CTLMenu{

  public:
    
    CTLMenu(LiquidCrystal* _lcd,LiquidMenu* _menu,HUBOut* __hubOut);

    void setup() ;

    void ping();
  
    void enable();

    void disable();

    void updateDisplay(char* l1, char* l2);

    void updateDisplayTmp();

    void loop();

    void handleMainMenu();

    void handleSensorsMenu();

    void ok();

    void up();

    void down();

    void previous();

    void debug(String message);
    
    void debug(uint8_t message);
};

#endif