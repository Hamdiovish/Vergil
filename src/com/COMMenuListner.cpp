#include "Arduino.h"
#include "utilities/Injector.h"

#include <com/COMMenuListner.h>
#include "com/COMMenu.h"

void blankFunction(){};


void selectedGoMain(){
      Serial.println(">>selectedGoMain():");
      comMenu->menu->change_screen(comMenu->main_screen);
      comMenu->menu->set_focusedLine(0);
};

void selectedOptionIp(){
      Serial.println(">>selectedOptionIp:");
      String l1= "IP:";
      String l2= "192.168.4.1";
      comMenu->displayDataScreen(l1,l2,comMenu->settings_screen);
}

void selectedOptionPh(){
      Serial.println(">>selectedOptionPh:");
      String l1= "Ph:";
      String l2= "5.8";
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen);
}

void selectedOptionEc(){
      Serial.println(">>selectedOptionEc:");
      String l1= "Ec:";
      String l2= "2.3";
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen);
}

void selectedOptionLight(){
      Serial.println(">>selectedOptionLight:");
      String l1= "Light:";
      String l2= "6680Lux";
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen);
}

void selectedCo2(){
      Serial.println(">>selectedCo2:");
      String l1= "Co2:";
      int co2=snsMhz->getCo2();
      String l2=String(co2);
      l2+="ppm";
      Serial.println(l2);
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen); 
}

void selectedHumidity(){
      Serial.println(">>selectedHumidity:");
      double display=snsDht11->getHumidity();
      String l1= "Humidity:";
      String l2= String(display);
      l2+="%";      
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen); 
}

void selectedTemperature(){
      Serial.println(">>selectedTemperature:");
      double display=snsDht11->getTemperature();
      String l2= String(display);
      String l1= "Temperature:";
      l2+="C"; 
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen); 
}


void selectedWaterTemperature(){
      Serial.println(">>selectedWaterTemperature:");
      double display=snsDallas->getTemperature();
      String l2= String(display);
      String l1= "Water Temp.:";
      l2+="C"; 
      comMenu->displayDataScreen(l1,l2,comMenu->sensors_screen); 
}

void selectedTime(){
      Serial.println(">>selectedTime:");
      char* c="";
      hubOut->displayTime(c);
      String l1= "Time:";
      String l2= String(c);
      comMenu->displayDataScreen(l1,l2,comMenu->settings_screen);
}

void selectedGoSensors(){
      Serial.println(">>selectedGoSensors():");
      comMenu->menu->change_screen(comMenu->sensors_screen);
      comMenu->menu->set_focusedLine(0);
      comMenu->menu->update();
}
void selectedGoSettings(){
      Serial.println(">>selectedGoSettings():");
      comMenu->menu->change_screen(comMenu->settings_screen);
      comMenu->menu->set_focusedLine(0);
      comMenu->menu->update();
}

void selectedGoWelcome(){
      Serial.println(">>selectedGoWelcome():");
      comMenu->menu->change_screen(comMenu->welcome_screen);
      comMenu->menu->set_focusedLine(0);
      comMenu->menu->update();
}

void selectedSettingsExit(){
      Serial.println(">>selectedSettingsExit():");
      comMenu->menu->change_screen(comMenu->main_screen);
      comMenu->menu->update();
}

void selectedSensorsExit(){
      Serial.println(">>selectedSensorsExit():");
      comMenu->menu->change_screen(comMenu->main_screen);
      comMenu->menu->update();
}

void selectedMainExit(){
      Serial.println(">>selectedMainExit():");
      comMenu->menu->change_screen(comMenu->welcome_screen);
      comMenu->menu->update();
}

void exitDataScreen(){
      Serial.println(">>exitData():");
      comMenu->menu->change_screen(comMenu->back_screen); 
      comMenu->menu->update();
}