#include "Arduino.h"
#include "utilities/Injector.h"

#include <com/COMMenuListner.h>
#include "com/COMMenu.h"

void blankFunction(){};


void selectedGoController(){
      Serial.println(">>selectedGoController():");
      comMenu->menu->change_screen(comMenu->controllers_screen);
      comMenu->menu->set_focusedLine(0);
};

void selectedGoBackToController(){
      Serial.println(">>selectedGoBackToController():");
      comMenu->menu->change_screen(comMenu->controllers_screen);
};

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

void controllerFanOn(){
     ctlVentilo->on(); 
      selectedGoBackToController();
}
void controllerFanOff(){
     ctlVentilo->off();       
      selectedGoBackToController();
}

void controllerFanDirectionOn(){
      ctlVentilo->clockWise();    
      selectedGoBackToController();
}
void controllerFanDirectionOff(){
      ctlVentilo->antiClockWise();
      selectedGoBackToController();
}

void controllerMainPumpOn(){
      ctlMainPump->on();
      selectedGoBackToController();
}
void controllerMainPumpOff(){
      ctlMainPump->off();   
      selectedGoBackToController();
}

void controllerSwitchPumpOn(){
      ctlSwitchPump->on();
      selectedGoBackToController();
}
void controllerSwitchPumpOff(){
      ctlSwitchPump->off();   
      selectedGoBackToController();
}

void controllerLightOn(){
      ctlLight->on();
      selectedGoBackToController();
}
void controllerLightOff(){
      ctlLight->off();   
      selectedGoBackToController();
}

void controllerHeaterOn(){
      ctlHeater->on();
      selectedGoBackToController();
}
void controllerHeaterOff(){
      ctlHeater->off();   
      selectedGoBackToController();
}

void selectedControllerFan(){
      Serial.println(">>selectedControllerFan:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerFanOn,controllerFanOff); 
};

void selectedControllerFanDirection(){
      Serial.println(">>selectedControllerFanDirection:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerFanDirectionOn,controllerFanDirectionOn); 
};

void selectedControllerMainPump(){
      Serial.println(">>selectedControllerMainPump:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerMainPumpOn,controllerMainPumpOff); 
};

void selectedControllerSwitchPump(){
      Serial.println(">>selectedControllerSwitchPump:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerSwitchPumpOn,controllerSwitchPumpOff); 
};

void selectedControllerLight(){
      Serial.println(">>selectedControllerLight:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerLightOn,controllerLightOff); 
};

void selectedControllerHeater(){
      Serial.println(">>selectedControllerHeater:");
      String l1= "On";
      String l2= "Off";
      comMenu->displayControllerScreen(l1,l2,comMenu->controllers_screen,controllerHeaterOn,controllerHeaterOff); 
};

void selectedControllerExit(){
      Serial.println(">>exitController():");
      comMenu->menu->change_screen(comMenu->main_screen); 
      comMenu->menu->update();
};
