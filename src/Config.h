#ifndef CONFIG_H
#define CONFIG_H

bool DEBUG = true;
////////// START SYSTEM SPI //////////
/*
 SPI     ARD 1284
 MOSI     11  6
 MISO     12  7
 CLK|SCK  13  8
*/
////////// END SYSTEM SPI //////////

////////// START SYSTEM I2C //////////
/*
 SPI     ARD  1284
 SCL     A5    22
 SDA     A4    23
*/
////////// END SYSTEM I2C //////////

////////// SSPI: START DIGITAL INPUT - 74HC165 //////////
/*
//CHAIN: http://www.gammon.com.au/forum/?id=11979
//SPI: http://www.gammon.com.au/forum/?id=11979
//BITBANG: http://www.gammon.com.au/forum/?id=10892
 HC ARD  1284
 08 GND   GND
 16 VCC   VCC
 01 02  (18) 12  PL  LOAD
 02 03  (19) 13  CLK SCK
 07 04  (20) 14  Q7|   // Serial output (Pin 9) or complementary output (Pin 7) of 74165 is connected to the digital pin 2 of Arduino UNO.
 15 08    GND
 
 03 SNS_DIG_MAIN_PUMP
 04 SNS_DIG_SWITCH_PUMP_TOP
 05 SNS_DIG_SWITCH_PUMP_BOTTOM
*/
#define PIN_ARD_SNS_DGT_LOAD 12  // SH/LD (Pin 1) of 74165 is connected to the digital pin 7 of Arduino UNO.
#define PIN_ARD_SNS_DGT_SCLK 13  // CS (Pin 15) of 74165 is connected to the digital pin 8 of Arduino UNO.
#define PIN_ARD_SNS_DGT_DATA 14

#define SNS_DGT_MAIN_PUMP          4
#define SNS_DGT_SWITCH_PUMP_TOP    5
#define SNS_DGT_SWITCH_PUMP_BOTTOM 6

#define INTERVAL_SNS_DGT  2500
//////////END DIGITAL INPUT//////////

//////////START DHT//////////
/*
DHT      ARD     1284
DATA     A3     (40)A0
*/
#define PIN_ARD_SNS_DHT_DATA A0

#define IDL_TEMPERATURE 24
#define MIN_TEMPERATURE 20
#define MAX_TEMPERATURE 28
#define IDL_TEMPERATURE_INTERVAL 2
#define CRASH_MIN_TEMPERATURE 10
#define CRASH_MAX_TEMPERATURE 30

#define IDL_HUMIDITY 85
#define MIN_HUMIDITY 75
#define MAX_HUMIDITY 90
#define IDL_HUMIDITY_INTERVAL 5
#define CRASH_MIN_HUMIDITY 60
#define CRASH_MAX_HUMIDITY 95

#define INTERVAL_SNS_DHT 2500
//////////END DHT//////////

//////////START HUB OUT - 74HC595 //////////
/*
//SPI:http://www.gammon.com.au/forum/?id=11518
//SPI:http://www.gammon.com.au/spi
HC  ARD      1284
08: GND      GND
13: GND      GND
16: VCC      VCC
10: VCC      VCC
14: 11-SPI   6      DATA
11: 13-SPI   8     CLK-SPI
12: 09 RSK   (3)2  LATCH
01: HUB_ENTRY_HEATER
..: ..
*/
#define HUB_OUT_COUNT               1
#define PIN_ARD_HUB_OUT_SS_LATCH    2

#define HUB_ENTRY_HEATER            1
#define HUB_ENTRY_VENTILO_POWER     2
#define HUB_ENTRY_VENTILO_DIRECTION 3
#define HUB_ENTRY_MAIN_PUMP         4
#define HUB_ENTRY_SWITCH_PUMP       5
#define HUB_ENTRY_LIGHT             6
//////////END HUB OUT//////////

////////// SPI: START LCD - 74HC595 ////////
/*
HC  LCD
01  08
03  09
04  04
05  05
06  06
07  07
08  GND

HC  ARD      1284
10  VCC
11  13-SPI
12  9        (2)1
13  GND | CE:ON/OFF
14  11-SPI
16  VCC
*/
#define PIN_ARD_LCD_CS  1
//////////END LCD - 74HC595 //////////

////////// SPI: START SD ////////
/*
SD    ARD       1284
CS    8         (1)0
VCC   VCC
GND   GND
MOSI  11-SPI
MISO  12-SPI
SCK   13-SPI
*/
#define PIN_ARD_SD_CS  0
//////////END SD ////////

////////// I2C: START RTC DS3231  ////////
/*
http://osoyoo.com/2017/09/12/arduino-lesson-real-time-clock-rtc-module-ds3231/
SD    ARD
VCC   VCC
GND   GND
SCL   A5
SDA   A4
*/
#define I2C_ID_DS3231 104
//////////END RTC ////////

////////// START ESP8266  ////////
/*
SD    ARD   1284
VCC   VCC
GND   GND
TX     6    (16)10
RX     7    (17)11
*/
#define PIN_ARD_ESP_STX 10
#define PIN_ARD_ESP_RTX 11
//////////END ESP8266 ////////


////////// PWM: START MHZ  ////////
/*
MH      ARD     1284
pmw     5       (4)3
*/
#define PIN_ARD_MHZ 3
//////////END MHZ ////////

////////// START IR  ////////
/*
IR      ARD     1284
DATA    A0     (29)23
*/
#define PIN_ARD_IR 23
////////// END IR ////////

//
#endif

//platformio lib -g install /root/Arduino/libraries/SD.zip