#ifndef CTL_MENU_H
#define CTL_MENU_H

#include "Arduino.h"
#include <ShiftedLCD.h>
#include <LiquidMenu.h>
#include "SNSDht11.h"
#include "Config.h"
#include "Global.h"
#include "CTLMenuListner.h"

extern class  LiquidCrystal* lcd; 
extern class  LiquidMenu* menu;
extern class  LiquidScreen* welcome_screen;
extern class  LiquidScreen* data_screen;
extern class  LiquidScreen* main_screen;
extern class  LiquidScreen* sensors_screen;
extern class  LiquidScreen* settings_screen;
extern class  LiquidScreen* back_screen;

extern class  LiquidLine* welcome_line_1;
extern class  LiquidLine* welcome_line_2;

extern class  LiquidLine* data_line_1;
extern class  LiquidLine* data_line_2;

extern class  LiquidLine* main_option_line_1;
extern class  LiquidLine* main_option_line_2;
extern class  LiquidLine* main_option_line_3;
extern class  LiquidLine* main_option_line_4;
extern class  LiquidLine* main_option_line_5;

extern class  LiquidLine* sensors_option_line_1;
extern class  LiquidLine* sensors_option_line_2;
extern class  LiquidLine* sensors_option_line_3;
extern class  LiquidLine* sensors_option_line_4;
extern class  LiquidLine* sensors_option_line_5;
extern class  LiquidLine* sensors_option_line_6;
extern class  LiquidLine* sensors_option_line_7;
extern class  LiquidLine* sensors_option_line_8;

extern class  LiquidLine* settings_option_line_1;
extern class  LiquidLine* settings_option_line_2;
extern class  LiquidLine* settings_option_line_3;

extern boolean enabled;
extern boolean autoBackstepRequest;
extern long lastMs_nextScreen;
extern long period_nextScreen;

extern char* line1;
extern char* line2;

class CTLMenu{

  public:
    
    LiquidMenu* menu;
  
    LiquidCrystal* lcd; 

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
};

#endif