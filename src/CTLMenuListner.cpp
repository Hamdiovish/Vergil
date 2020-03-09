#include "Arduino.h"
#include "Injector.h"

#include <CTLMenuListner.h>
#include "CTLMenu.h"

void blankFunction(){};


void selectedGoMain(){
      Serial.println(">>selectedGoMain():");
      ctlMenu->menu->change_screen(ctlMenu->main_screen);
      ctlMenu->menu->set_focusedLine(0);
};

void selectedOptionIp(){
      Serial.println(">>selectedOptionIp:");
      String l1= "IP:";
      String l2= "192.168.4.1";
      ctlMenu->displayDataScreen(l1,l2,ctlMenu->settings_screen);
}


void selectedCo2(){
      Serial.println(">>selectedCo2:");
      String l1= "Co2:";
      double co2=snsMhz->getCo2();
      String l2= String(co2);
      l2+="ppm";
      ctlMenu->displayDataScreen(l1,l2,ctlMenu->sensors_screen); 
}

void selectedHumidity(){
      Serial.println(">>selectedHumidity:");
      double display=snsDht11->getHumidity();
      String l1= "Humidity:";
      String l2= String(display);
      l2+="%";      
      ctlMenu->displayDataScreen(l1,l2,ctlMenu->sensors_screen); 
}

void selectedTemperature(){
      Serial.println(">>selectedTemperature:");
      double display=snsDht11->getTemperature();
      String l2= String(display);
      String l1= "Temperature:";
      l2+="C"; 
      ctlMenu->displayDataScreen(l1,l2,ctlMenu->sensors_screen); 
}

void selectedTime(){
      Serial.println(">>selectedTime:");
      char* c="";
      hubOut->displayTime(c);
      String l1= "Time:";
      String l2= String(c);
      ctlMenu->displayDataScreen(l1,l2,ctlMenu->sensors_screen);
}

void selectedGoSensors(){
      Serial.println(">>selectedGoSensors():");
      ctlMenu->menu->change_screen(ctlMenu->sensors_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}

void selectedGoSettings(){
      Serial.println(">>selectedGoSettings():");
      ctlMenu->menu->change_screen(ctlMenu->settings_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}

void selectedGoWelcome(){
      Serial.println(">>selectedGoWelcome():");
      ctlMenu->menu->change_screen(ctlMenu->welcome_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}

void selectedSettingsExit(){
      Serial.println(">>selectedSettingsExit():");
      ctlMenu->menu->change_screen(ctlMenu->main_screen);
      ctlMenu->menu->update();
}

void selectedSensorsExit(){
      Serial.println(">>selectedSensorsExit():");
      ctlMenu->menu->change_screen(ctlMenu->main_screen);
      ctlMenu->menu->update();
}

void selectedMainExit(){
      Serial.println(">>selectedMainExit():");
      ctlMenu->menu->change_screen(ctlMenu->welcome_screen);
      ctlMenu->menu->update();
}

void exitDataScreen(){
      Serial.println(">>exitData():");
      ctlMenu->menu->change_screen(ctlMenu->back_screen); 
      ctlMenu->menu->update();
}