#include "CTLMenu.h"
#include "Config.h"
#include <LiquidMenu.h>
#include "HUBOut.h"
#include "SNSDht11.h"
#include "Global.h"
#include "Injector.h"
#include "CTLMenuListner.h"



 CTLMenu::CTLMenu(LiquidCrystal* _lcd,LiquidMenu* _menu){
  lcd=_lcd;
  menu=_menu;

  boolean enabled=true;
  boolean autoBackstepRequest=false;
  long lastMs_nextScreen=0;
  long period_nextScreen=3000;

  char* line1="Data title";
  char* line2="Data value";
}

 void CTLMenu::setup() {
  debug("setup()");

  welcome_line_1 = new  LiquidLine(0, 0, "|    VERGIL    |");
  welcome_line_2 = new  LiquidLine(0, 1, "|  Auto Farm   |");
  welcome_line_1->attach_function(1, selectedGoMain);
  welcome_line_2->attach_function(1, selectedGoMain);

  welcome_screen = new  LiquidScreen(*welcome_line_1, *welcome_line_2);

  welcome_screen->set_focusPosition(Position::CUSTOM);

  data_line_1 = new  LiquidLine(0, 0,line1);
  data_line_2 = new  LiquidLine(0, 1,line2);
  data_line_1->attach_function(1, exitDataScreen);
  data_line_1->attach_function(1, exitDataScreen);

  data_screen = new LiquidScreen(*data_line_1,*data_line_2);
  data_screen->set_focusPosition(Position::CUSTOM);

  handleMainMenu();
  handleSensorsMenu();
  handleSettingsMenu();
  
  lcd->begin(16, 2);

  menu->add_screen(*welcome_screen);
  menu->add_screen(*data_screen);
  menu->change_screen(welcome_screen);
  menu->set_focusedLine(0);
  /*
  menu->set_focusPosition(Position::LEFT);
  byte lFocus[8] = {
    0b00000,
    0b00100,
    0b00010,
    0b11111,
    0b00010,
    0b00100,
    0b00000,
    0b00000
  };
	menu->set_focusSymbol(Position::LEFT, lFocus);
  */
  menu->update();
}


void CTLMenu::displayDataScreen(String l1,String l2,LiquidScreen* current){
      back_screen=current;
      strcpy(line1, l1.c_str()); 
      strcpy(line2, l2.c_str()); 
      data_line_1->attach_function(1, exitDataScreen);
      data_line_2->attach_function(1, exitDataScreen);
      menu->change_screen(data_screen);
      data_screen->set_focusPosition(Position::CUSTOM);
      menu->set_focusedLine(1);
      menu->update();
}

void CTLMenu::ping(){
   debug("ping()");
}

void CTLMenu::enable(){
  debug("enabled()");
  enabled=true;
}

void CTLMenu::disable(){
  debug("disabled()");
  enabled=false;
}

void CTLMenu::updateDisplay(char* l1, char* l2){
  line1=l1;
  line2=l2;
  menu->change_screen(data_screen);
  menu->update();
}

void CTLMenu::updateDisplayTmp(){
  line1="Time:";
  hubOut->displayTime(line2);
  menu->change_screen(data_screen);
  menu->update();
  
}

void CTLMenu::loop(){
}


void CTLMenu::handleSettingsMenu(){
  settings_option_line_1 = new  LiquidLine(1, 1, "Ip");
  settings_option_line_2 = new  LiquidLine(1, 1, "Export Data");
  settings_option_line_3 = new  LiquidLine(1, 1, "exit");
  settings_option_line_1->attach_function(1, selectedOptionIp);
  settings_option_line_2->attach_function(1, blankFunction);
  settings_option_line_3->attach_function(1, selectedSettingsExit);
  settings_screen = new LiquidScreen();
  settings_screen->add_line(*settings_option_line_1);
  settings_screen->add_line(*settings_option_line_2);
  settings_screen->add_line(*settings_option_line_3);
  settings_screen->set_displayLineCount(2);
  settings_screen->set_focusPosition(Position::LEFT);
  menu->add_screen(*settings_screen);  
}

void CTLMenu::handleMainMenu(){
  main_option_line_1 = new  LiquidLine(1, 1, "Sensors");
  main_option_line_2 = new  LiquidLine(1, 1, "Controllers");
  main_option_line_3 = new  LiquidLine(1, 1, "Components");
  main_option_line_4 = new  LiquidLine(1, 1, "Settings");
  main_option_line_5 = new  LiquidLine(1, 1, "exit");
  main_option_line_1->attach_function(1, selectedGoSensors);
  main_option_line_2->attach_function(1, blankFunction);
  main_option_line_3->attach_function(1, blankFunction);
  main_option_line_4->attach_function(1, selectedGoSettings);
  main_option_line_5->attach_function(1, selectedMainExit);
  main_screen = new LiquidScreen();
  main_screen->add_line(*main_option_line_1);
  main_screen->add_line(*main_option_line_2);
  main_screen->add_line(*main_option_line_3);
  main_screen->add_line(*main_option_line_4);
  main_screen->add_line(*main_option_line_5);
  main_screen->set_displayLineCount(2);
  main_screen->set_focusPosition(Position::LEFT);
  menu->add_screen(*main_screen);
}

void CTLMenu::handleSensorsMenu(){
  sensors_option_line_1 = new  LiquidLine(1, 1, "Time");
  sensors_option_line_2 = new  LiquidLine(1, 1, "Temperature");
  sensors_option_line_3 = new  LiquidLine(1, 1, "Humidity");
  sensors_option_line_4 = new  LiquidLine(1, 1, "Co2");
  sensors_option_line_5 = new  LiquidLine(1, 1, "Light");
  sensors_option_line_6 = new  LiquidLine(1, 1, "PH");
  sensors_option_line_7 = new  LiquidLine(1, 1, "EC");
  sensors_option_line_8 = new  LiquidLine(1, 1, "Exit");
  sensors_option_line_1->attach_function(1, selectedTime);
  sensors_option_line_2->attach_function(1, selectedTemperature);
  sensors_option_line_3->attach_function(1, selectedHumidity);
  sensors_option_line_4->attach_function(1, selectedCo2);
  sensors_option_line_5->attach_function(1, blankFunction);
  sensors_option_line_6->attach_function(1, blankFunction);
  sensors_option_line_7->attach_function(1, blankFunction);
  sensors_option_line_8->attach_function(1, selectedSensorsExit);
  sensors_screen = new LiquidScreen();
  sensors_screen->add_line(*sensors_option_line_1);
  sensors_screen->add_line(*sensors_option_line_2);
  sensors_screen->add_line(*sensors_option_line_3);
  sensors_screen->add_line(*sensors_option_line_4);
  sensors_screen->add_line(*sensors_option_line_5);
  sensors_screen->add_line(*sensors_option_line_6);
  sensors_screen->add_line(*sensors_option_line_7);
  sensors_screen->add_line(*sensors_option_line_8);
  sensors_screen->set_displayLineCount(2);
  sensors_screen->set_focusPosition(Position::LEFT);
  menu->add_screen(*sensors_screen);
} 


boolean::CTLMenu::checkNavigationScreen(){
  if(menu->get_currentScreen() == data_screen || menu->get_currentScreen() == welcome_screen){
    return false;
  }
  return true;
}

void CTLMenu::ok(){
  uint8_t here = menu->get_focusedLine();
  menu->call_function(1);
  debug(">>ok:");
  debug(here);
}

void CTLMenu::up(){
  if(checkNavigationScreen()){
    menu->switch_focus(false);  
  }else{
    menu->call_function(1);
  }
  menu->update();
}

void CTLMenu::down(){
  if(checkNavigationScreen()){
    menu->switch_focus(true);  
  }else{
    menu->call_function(1);
  }  
  menu->update();
}

void CTLMenu::previous(){
  menu->previous_screen();
  menu->update();
}

void CTLMenu::debug(String message){
  if(VG_DEBUG){
    Serial.print("CTLMenu: ");
    Serial.println(message);      
  }
}

void CTLMenu::debug(uint8_t message){
  if(VG_DEBUG){
    Serial.print("CTLMenu: ");
    Serial.println(message);      
  }
}