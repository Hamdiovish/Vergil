#include "com/COMMenu.h"
#include "utilities/Config.h"
#include <LiquidMenu.h>
#include "controllers/HUBOut.h"
#include "sensors/SNSDht11.h"
#include "utilities/Global.h"
#include "utilities/Injector.h"
#include "com/COMMenuListner.h"



 COMMenu::COMMenu(LiquidCrystal* _lcd,LiquidMenu* _menu){
  lcd=_lcd;
  menu=_menu;

  boolean enabled=true;
  boolean autoBackstepRequest=false;
  long lastMs_nextScreen=0;
  long period_nextScreen=3000;

  char* line1="Data title";
  char* line2="Data value";

  char* controllerlLine1="On";
  char* controllerlLine2="Off";
}

 void COMMenu::setup() {
  debug("setup()");

  welcome_line_1 = new  LiquidLine(0, 0, "|    VERGIL    |");
  welcome_line_2 = new  LiquidLine(0, 1, "|  Auto Farm   |");
  welcome_line_1->attach_function(1, selectedGoMain);
  welcome_line_2->attach_function(1, selectedGoMain);

  welcome_screen = new  LiquidScreen(*welcome_line_1, *welcome_line_2);

  welcome_screen->set_focusPosition(Position::CUSTOM);

  data_line_1 = new  LiquidLine(0, 0,line1);
  data_line_2 = new  LiquidLine(1, 1,line2);
  data_line_1->attach_function(1, exitDataScreen);
  data_line_2->attach_function(1, exitDataScreen);
  
  controller_line_1 = new  LiquidLine(1, 0,controllerlLine1);
  controller_line_2 = new  LiquidLine(1, 1,controllerlLine2);
  controller_line_1->attach_function(1, blankFunction);
  controller_line_2->attach_function(1, blankFunction);

  data_screen = new LiquidScreen(*data_line_1,*data_line_2);
  data_screen->set_focusPosition(Position::LEFT);

  controller_screen = new LiquidScreen(*controller_line_1,*controller_line_2);
  controller_screen->set_focusPosition(Position::LEFT);

  handleMainMenu();
  handleSensorsMenu();
  handleSettingsMenu();
  handleControllersMenu();
  
  lcd->begin(16, 2);

  menu->add_screen(*welcome_screen);
  menu->add_screen(*data_screen);
  menu->add_screen(*controller_screen);
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


void COMMenu::displayControllerScreen(String l1,String l2,LiquidScreen* current, void (*on)(void), void (*off)(void)){
      Serial.println(">>Conroller:");
      Serial.println(l1);
      Serial.println(l2);

      back_screen=current;
      strcpy(controllerlLine1, l1.c_str()); 
      strcpy(controllerlLine2, l2.c_str()); 
      controller_line_1->attach_function(1, on);
      controller_line_2->attach_function(1, off);
      menu->change_screen(controller_screen);
     // data_screen->set_focusPosition(Position::LEFT);
      menu->set_focusedLine(0);
      menu->update();
}
void COMMenu::displayDataScreen(String l1,String l2,LiquidScreen* current){
      Serial.println(">>DATA:");
      Serial.println(l1);
      Serial.println(l2);

      back_screen=current;
      strcpy(line1, l1.c_str()); 
      strcpy(line2, l2.c_str()); 
      data_line_1->attach_function(1, exitDataScreen);
      data_line_2->attach_function(1, exitDataScreen);
      menu->change_screen(data_screen);
     // data_screen->set_focusPosition(Position::LEFT);
      menu->set_focusedLine(1);
      menu->update();
}

void COMMenu::ping(){
   debug("ping()");
}

void COMMenu::enable(){
  debug("enabled()");
  enabled=true;
}

void COMMenu::disable(){
  debug("disabled()");
  enabled=false;
}

void COMMenu::updateDisplay(char* l1, char* l2){
  line1=l1;
  line2=l2;
  menu->change_screen(data_screen);
  menu->update();
}

void COMMenu::updateDisplayTmp(){
  line1="Time:";
  hubOut->displayTime(line2);
  menu->change_screen(data_screen);
  menu->update();
  
}

void COMMenu::loop(){
}
void COMMenu::handleControllersMenu(){
  controllers_option_line_1 = new  LiquidLine(1, 1, "Fan");
  controllers_option_line_2 = new  LiquidLine(1, 1, "Fan direction");
  controllers_option_line_3 = new  LiquidLine(1, 1, "Main pump");
  controllers_option_line_4 = new  LiquidLine(1, 1, "Swich pump");
  controllers_option_line_5 = new  LiquidLine(1, 1, "Light");
  controllers_option_line_6 = new  LiquidLine(1, 1, "Heater");
  controllers_option_line_7 = new  LiquidLine(1, 1, "Exit");
  controllers_option_line_1->attach_function(1, selectedControllerFan);
  controllers_option_line_2->attach_function(1, selectedControllerFanDirection);
  controllers_option_line_3->attach_function(1, selectedControllerMainPump);
  controllers_option_line_4->attach_function(1, selectedControllerSwitchPump);
  controllers_option_line_5->attach_function(1, selectedControllerLight);
  controllers_option_line_6->attach_function(1, selectedControllerHeater);
  controllers_option_line_7->attach_function(1, selectedControllerExit);
  controllers_screen = new LiquidScreen();
  controllers_screen->add_line(*controllers_option_line_1);
  controllers_screen->add_line(*controllers_option_line_2);
  controllers_screen->add_line(*controllers_option_line_3);
  controllers_screen->add_line(*controllers_option_line_4);
  controllers_screen->add_line(*controllers_option_line_5);
  controllers_screen->add_line(*controllers_option_line_6);
  controllers_screen->add_line(*controllers_option_line_7);
  controllers_screen->set_displayLineCount(2);
  controllers_screen->set_focusPosition(Position::LEFT);
  menu->add_screen(*controllers_screen);  
}

void COMMenu::handleSettingsMenu(){
  settings_option_line_1 = new  LiquidLine(1, 1, "Time");
  settings_option_line_2 = new  LiquidLine(1, 1, "Ip");
  settings_option_line_3 = new  LiquidLine(1, 1, "Export Data");
  settings_option_line_4 = new  LiquidLine(1, 1, "exit");
  settings_option_line_1->attach_function(1, selectedTime);
  settings_option_line_2->attach_function(1, selectedOptionIp);
  settings_option_line_3->attach_function(1, blankFunction);
  settings_option_line_4->attach_function(1, selectedSettingsExit);
  settings_screen = new LiquidScreen();
  settings_screen->add_line(*settings_option_line_1);
  settings_screen->add_line(*settings_option_line_2);
  settings_screen->add_line(*settings_option_line_3);
  settings_screen->add_line(*settings_option_line_4);
  settings_screen->set_displayLineCount(2);
  settings_screen->set_focusPosition(Position::LEFT);
  menu->add_screen(*settings_screen);  
}

void COMMenu::handleMainMenu(){
  main_option_line_1 = new  LiquidLine(1, 1, "Sensors");
  main_option_line_2 = new  LiquidLine(1, 1, "Controllers");
  main_option_line_3 = new  LiquidLine(1, 1, "Components");
  main_option_line_4 = new  LiquidLine(1, 1, "Settings");
  main_option_line_5 = new  LiquidLine(1, 1, "exit");
  main_option_line_1->attach_function(1, selectedGoSensors);
  main_option_line_2->attach_function(1, selectedGoController);
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

void COMMenu::handleSensorsMenu(){
  sensors_option_line_1 = new  LiquidLine(1, 1, "Temperature");
  sensors_option_line_2 = new  LiquidLine(1, 1, "Water Temp.");
  sensors_option_line_3 = new  LiquidLine(1, 1, "Humidity");
  sensors_option_line_4 = new  LiquidLine(1, 1, "Co2");
  sensors_option_line_5 = new  LiquidLine(1, 1, "Light");
  sensors_option_line_6 = new  LiquidLine(1, 1, "PH");
  sensors_option_line_7 = new  LiquidLine(1, 1, "EC");
  sensors_option_line_8 = new  LiquidLine(1, 1, "Exit");
  sensors_option_line_1->attach_function(1, selectedTemperature);
  sensors_option_line_2->attach_function(1, selectedWaterTemperature);
  sensors_option_line_3->attach_function(1, selectedHumidity);
  sensors_option_line_4->attach_function(1, selectedCo2);
  sensors_option_line_5->attach_function(1, selectedOptionLight);
  sensors_option_line_6->attach_function(1, selectedOptionPh);
  sensors_option_line_7->attach_function(1, selectedOptionEc);
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


boolean::COMMenu::checkNavigationScreen(){
  if(menu->get_currentScreen() == data_screen || menu->get_currentScreen() == welcome_screen){
    return false;
  }
  return true;
}

void COMMenu::ok(){
  uint8_t here = menu->get_focusedLine();
  menu->call_function(1);
  debug(">>ok:");
  debug(here);
}

void COMMenu::up(){
  if(checkNavigationScreen()){
    menu->switch_focus(false);  
  }else{
    menu->call_function(1);
  }
  menu->update();
}

void COMMenu::down(){
  if(checkNavigationScreen()){
    menu->switch_focus(true);  
  }else{
    menu->call_function(1);
  }  
  menu->update();
}

void COMMenu::previous(){
  menu->previous_screen();
  menu->update();
}

void COMMenu::debug(String message){
  if(VG_DEBUG){
    Serial.print("COMMenu: ");
    Serial.println(message);      
  }
}

void COMMenu::debug(uint8_t message){
  if(VG_DEBUG){
    Serial.print("COMMenu: ");
    Serial.println(message);      
  }
}