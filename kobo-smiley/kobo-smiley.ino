/****************************************************************************************************************************

# kobo-smiley
kobo lowcost smiley button based on esp8266 with captive portal for configuration

  *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

//Libraries needed to post to Kobo API
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Define the button pin and led
// To be updated so there is only one led
const int ledgreen    = D1;     
const int buttongreen = D2;     
const int ledyellow    = D3;     
const int buttonyellow = D6; 
const int ledred    = D8;     
const int buttonred = D7; 


ESPAsync_WiFiManager_Lite* ESPAsync_WiFiManager;

void heartBeatPrint()
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print("H");        // H means connected to WiFi
  else
  {
    if (ESPAsync_WiFiManager->isConfigMode())
      Serial.print("C");     
    //  int status = 0;   // C means in Config Mode
    else
      Serial.print("F");        // F means not connected to WiFi
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    20000L
  // Print hearbeat every HEARTBEAT_INTERVAL (20) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] PROGMEM =
  "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}"\
  "button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  //for the button
  pinMode(ledgreen,OUTPUT);
  pinMode(buttongreen,INPUT_PULLUP); 
  pinMode(ledyellow,OUTPUT);
  pinMode(buttonyellow,INPUT_PULLUP); 
  pinMode(ledred,OUTPUT);
  pinMode(buttonred,INPUT_PULLUP); 


  // Debug console
  Serial.begin(115200);
  while (!Serial);
  delay(200);
  Serial.print(F("\nStarting ESPAsync_WiFi using "));
  Serial.print(FS_Name);
  Serial.print(F(" on "));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP_ASYNC_WIFI_MANAGER_LITE_VERSION);

#if USING_MRD
  Serial.println(ESP_MULTI_RESET_DETECTOR_VERSION);
#else
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);
#endif


// Name of the AP when not configure
  ESPAsync_WiFiManager = new ESPAsync_WiFiManager_Lite();
  String AP_SSID = "kobo-smiley";
  String AP_PWD  = "kobo-smiley123456";
  
  // Set customized AP SSID and PWD
  ESPAsync_WiFiManager->setConfigPortal(AP_SSID, AP_PWD);

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //ESPAsync_WiFiManager->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  ESPAsync_WiFiManager->setConfigPortalChannel(0);

#if USING_CUSTOMS_STYLE
  ESPAsync_WiFiManager->setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  ESPAsync_WiFiManager->setCustomsHeadElement(PSTR("<style>html{filter: invert(10%);}</style>"));
#endif

#if USING_CORS_FEATURE
  ESPAsync_WiFiManager->setCORSHeader(PSTR("Your Access-Control-Allow-Origin"));
#endif

  // Set customized DHCP HostName
  ESPAsync_WiFiManager->begin(HOST_NAME);
  //Or use default Hostname "ESP_XXXXXX"
  //ESPAsync_WiFiManager->begin();

}
// Function to post to Kobo API using the parameters configured in the captive portal
void kobo(int option)
{
  // transform char to string for json processing
   String formid = koboformid;
  String quest = question;
  String option1 = optiona;
  String option2 = optionb;
  String option3 = optionc;

 String dataoption;
 if (option == 1) {
  dataoption = option1;
  }
 else if (option == 2) {
  dataoption = option2;
  }
  else if (option == 3) {
  dataoption = option3;
  }
  Serial.print("data option :");
  Serial.print(dataoption);

  // kobo jsonPayload
  String jsonPayload = "{\n"
                      "  \"id\":\"" + formid + "\",\n"
                      "  \"submission\":{\n"
                      "    \"" + question + "\":\"" + dataoption + "\",\n"
                      "    \"meta\": {\n"
                      "      \"instanceID\": \"\"\n"
                      "    }\n"
                      "  }\n"
                      "}";


 Serial.println(jsonPayload);

  // Specify the target URL using HTTPS
  String url = koboapi; // Note the use of "https://"
  //String url = "https://kc.kobotoolbox.org/api/v1/submissions.json"; // Note the use of "https://"
 Serial.print(koboapi);

   // Create a WiFiClientSecure object
  WiFiClientSecure client;
  client.setInsecure();

  // Create an HTTPClient object with HTTPS
  HTTPClient http;

  // Assuming kobotoken is a String
  String token = kobotoken;
  Serial.println(token);

 // Create a String for the "Token " part
  String tokenPart = "Token ";

 // Concatenate tokenPart and kobotoken
  String authorizationHeader = tokenPart + token;

  // Add headers to the request
  http.begin(client, url);
  Serial.println("Connecting to: " + url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", authorizationHeader);
  Serial.print(authorizationHeader);

  // Send the POST request with HTTPS
  int httpResponseCode = http.POST(jsonPayload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response Code: " + String(httpResponseCode));
    Serial.println("Response:\n" + response);
  } else {
    Serial.println("HTTP Error: " + http.errorToString(httpResponseCode));
  }

  // Cleanup
  http.end();

}


#if USE_DYNAMIC_PARAMETERS
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}

#endif

void loop()
{
  ESPAsync_WiFiManager->run();
  check_status();

  #if USE_DYNAMIC_PARAMETERS
  displayCredentialsInLoop();
  #endif

  // if no wifi is connected, the 3 leds lights up
  if (WiFi.status() != WL_CONNECTED) {
                digitalWrite(ledgreen, HIGH);
                 digitalWrite(ledyellow, HIGH);
                  digitalWrite(ledred, HIGH);
        Serial.println("config mode");
        }
    else {
         }

  // The 3 buttons parts

   if (digitalRead(buttongreen) == LOW) {
         digitalWrite(ledgreen, HIGH);
         kobo(1);
          Serial.println("LED Turned ON GREEN");
        delay(1000);
       }
    else {
        digitalWrite(ledgreen, LOW);
       }

   if (digitalRead(buttonyellow) == LOW) {
        digitalWrite(ledyellow, HIGH);
        kobo(2);
        Serial.println("LED Turned ON YELLOW");
        delay(1000);
       }
    else {
        digitalWrite(ledyellow, LOW);
       }

   if (digitalRead(buttonred) == LOW) {
        digitalWrite(ledred, HIGH);
        kobo(3);
        Serial.println("LED Turned ON RED");
        delay(1000);
       }
    else {
        digitalWrite(ledred, LOW);
       }

}