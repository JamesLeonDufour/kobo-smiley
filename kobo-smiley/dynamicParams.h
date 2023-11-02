/****************************************************************************************************************************
  dynamicParams.h
  For ESP8266 / ESP32 boards

  ESPAsync_WiFiManager_Lite (https://github.com/khoih-prog/ESPAsync_WiFiManager_Lite) is a library
  for the ESP32/ESP8266 boards to enable store Credentials in EEPROM/SPIFFS/LittleFS for easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/ESPAsync_WiFiManager_Lite
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <ESPAsync_WiFiManager_Lite.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_BLYNK_SERVER_LEN      60
#define MAX_BLYNK_TOKEN_LEN       60

char koboapi [MAX_BLYNK_SERVER_LEN + 1]  = "https://kc.kobotoolbox.org/api/v1/submissions.json";
char koboformid  [MAX_BLYNK_TOKEN_LEN + 1]   = "aC3GwTDaD4YetzJg5CEjb6";
char kobotoken [MAX_BLYNK_SERVER_LEN + 1]  = "f53a91f78a250c0ccbbade4e646a9694e01a3812";
char question [MAX_BLYNK_SERVER_LEN + 1]  = "question";
char optiona  [MAX_BLYNK_SERVER_LEN + 1]   = "good";
char optionb  [MAX_BLYNK_SERVER_LEN + 1]   = "average";
char optionc  [MAX_BLYNK_SERVER_LEN + 1]   = "bad";
//#define MAX_BLYNK_PORT_LEN        6
//char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

//#define MAX_MQTT_SERVER_LEN      34
//char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Kobo Api", koboapi,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Form ID", koboformid,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Kobo Token", kobotoken,  MAX_BLYNK_SERVER_LEN },
  { "que", "Question label", question, MAX_BLYNK_SERVER_LEN },
  { "op1", "Answer1 label", optiona, MAX_BLYNK_SERVER_LEN },
  { "op2", "Answer2 label", optionb, MAX_BLYNK_SERVER_LEN },
  { "op3", "Answer3 label", optionc, MAX_BLYNK_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS


#endif      //dynamicParams_h
