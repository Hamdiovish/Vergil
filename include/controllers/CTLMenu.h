#ifndef CTL_MENU_H
#define CTL_MENU_H

#include "Arduino.h"
#include <ShiftedLCD.h>
#include <LiquidMenu.h>
#include "sensors/SNSDht11.h"
#include "utilities/Config.h"
#include "utilities/Global.h"
#include "controllers/CTLMenuListner.h"



class CTLMenu{

  public:

    LiquidCrystal* lcd; 
    LiquidMenu* menu;

    LiquidScreen* welcome_screen;
    LiquidScreen* data_screen;
    LiquidScreen* main_screen;
    LiquidScreen* sensors_screen;
    LiquidScreen* settings_screen;
    LiquidScreen* back_screen;

    LiquidLine* welcome_line_1;
    LiquidLine* welcome_line_2;

    LiquidLine* data_line_1;
    LiquidLine* data_line_2;

    LiquidLine* main_option_line_1;
    LiquidLine* main_option_line_2;
    LiquidLine* main_option_line_3;
    LiquidLine* main_option_line_4;
    LiquidLine* main_option_line_5;

    LiquidLine* sensors_option_line_1;
    LiquidLine* sensors_option_line_2;
    LiquidLine* sensors_option_line_3;
    LiquidLine* sensors_option_line_4;
    LiquidLine* sensors_option_line_5;
    LiquidLine* sensors_option_line_6;
    LiquidLine* sensors_option_line_7;
    LiquidLine* sensors_option_line_8;

    LiquidLine* settings_option_line_1;
    LiquidLine* settings_option_line_2;
    LiquidLine* settings_option_line_3;

    boolean enabled;

    char* line1;
    char* line2;
    
    CTLMenu(LiquidCrystal* _lcd,LiquidMenu* _menu);

    void setup() ;

    void ping();
  
    void enable();

    void disable();

    void updateDisplay(char* l1, char* l2);

    void updateDisplayTmp();

    void loop();

    void handleMainMenu();

    void handleSensorsMenu();

    void handleSettingsMenu();

    void ok();

    void up();

    void down();

    void previous();

    void debug(String message);
    
    void debug(uint8_t message);

    void displayDataScreen(String l1,String l2,LiquidScreen* current);

    boolean checkNavigationScreen();

};

#endif