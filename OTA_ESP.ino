/*Auth : Algobel TI
  Thanks for all free libraries
  Over -The-Air Programming
  while performing OTA you need to remember to stop all the function  (Basically "LOW" the pins output)
  Recomended where you can't have the access to the module
  Need to be in same network (Laptop or Pc and the ESpWroom )
  if you need any help please send a email : niwantha@algobel.com
  always keep the basic codes , 
  
*/


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "TP"; // Router SSID
const char* password = "12345678"; // Change the password
const char* host = "OTA-AlgobelTI";

int led_pin = 16; // Testing purpose
void Switch(int d);
void setup() {
  Serial.begin(115200);

  /* switch on led */
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("...");
    Switch(2000); // if network failed , run this function to identify or you can put own function to run cont/...
  }


  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() { // switch off all the PINS
    analogWrite(led_pin, 1);
  });

  ArduinoOTA.onEnd([]() { // Just debug purpose
    analogWrite(led_pin, 0);
    delay(250);
    analogWrite(led_pin, 1);
    delay(250);
    
  });

  ArduinoOTA.onError([](ota_error_t error) {
    ESP.restart();
  });

  /* setup the OTA server */
  ArduinoOTA.begin();
  Serial.println("Ready");

}

void loop() {
  ArduinoOTA.handle();
  Switch(1000);
}

void Switch(int d) {
  digitalWrite(led_pin, HIGH);
  delay(d);
  digitalWrite(led_pin, LOW);
  delay(d);
}
