#include "Arduino.h"
#include "Injector.h"

#include <CTLMenuListner.h>
#include "CTLMenu.h"

void blankFunction(){

};

void selectedGoMain(){
      Serial.println(">>selectedGoMain():");
      ctlMenu->menu->change_screen(main_screen);
      ctlMenu->menu->set_focusedLine(0);
};

void selectedOptionIp(){
      Serial.println(">>selectedOptionIp:");
      line1="IP:";
      String str= "192.168.4.1";
      strcpy(line2, str.c_str()); 
      ctlMenu->menu->change_screen(data_screen);
      ctlMenu->menu->update();
      back_screen=settings_screen;
      autoBackstepRequest=true;
      lastMs_nextScreen=millis();
}

void selectedCo2(){
      Serial.println(">>selectedCo2:");
      line1="Co2:";
      double co2=snsMhz->getCo2();
      String str= String(co2);
      str+="ppm";
      strcpy(line2, str.c_str()); 
      ctlMenu->menu->change_screen(data_screen);
      ctlMenu->menu->update();
      back_screen=sensors_screen;
      autoBackstepRequest=true;
      lastMs_nextScreen=millis();
}

void selectedHumidity(){
      Serial.println(">>selectedHumidity:");
      line1="Humidity:";
      double display=snsDht11->getHumidity();
      String str= String(display);
      str+="%";
      strcpy(line2, str.c_str()); 
      ctlMenu->menu->change_screen(data_screen);
      ctlMenu->menu->update();
      back_screen=sensors_screen;
      autoBackstepRequest=true;
      lastMs_nextScreen=millis();
}

void selectedTemperature(){
      Serial.println(">>selectedTemperature:");
      line1="Temperature:";
      double display=snsDht11->getTemperature();
      String str= String(display);
      str+="C";
      strcpy(line2, str.c_str()); 
      ctlMenu->menu->change_screen(data_screen);
      ctlMenu->menu->update();
      back_screen=sensors_screen;
      autoBackstepRequest=true;
      lastMs_nextScreen=millis();
}

void selectedTime(){
      Serial.println(">>selectedTime:");
      line1="Time:";
      hubOut->displayTime(line2);
      ctlMenu->menu->change_screen(data_screen);
      ctlMenu->menu->update();
      back_screen=sensors_screen;
      autoBackstepRequest=true;
      lastMs_nextScreen=millis();
}

void selectedGoSensors(){
      Serial.println(">>selectedGoSensors():");
      ctlMenu->menu->change_screen(sensors_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}
void selectedGoSettings(){
      Serial.println(">>selectedGoSettings():");
      ctlMenu->menu->change_screen(settings_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}

void selectedGoWelcome(){
      Serial.println(">>selectedGoWelcome():");
      ctlMenu->menu->change_screen(welcome_screen);
      ctlMenu->menu->set_focusedLine(0);
      ctlMenu->menu->update();
}

void selectedSettingsExit(){
      Serial.println(">>selectedSettingsExit():");
      ctlMenu->menu->change_screen(main_screen);
      ctlMenu->menu->update();
}

void selectedSensorsExit(){
      Serial.println(">>selectedSensorsExit():");
      ctlMenu->menu->change_screen(main_screen);
      ctlMenu->menu->update();
}

void selectedMainExit(){
      Serial.println(">>selectedMainExit():");
      ctlMenu->menu->change_screen(welcome_screen);
      ctlMenu->menu->update();
}
