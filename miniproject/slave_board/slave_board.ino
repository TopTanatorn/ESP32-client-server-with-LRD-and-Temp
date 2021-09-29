#include <WiFi.h>
#include "LM.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
const int analogInPin = 36;
const char* ssid     = "xxxxxx";
const char* password = "xxxxxx";
LM LM;
IPAddress server (xxxx, xxxx, xxxx, xxxx); // add your server IP
Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();
// Initialize the client library
WiFiClient client;
void setup() {
  Serial.begin(115200);
  Serial.print("SSID: ");
  Serial.println(ssid);
  matrix.begin(0x70);  // pass in the address
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    if (client.connect(server, 80)) {
      Serial.println("connected");
      client.print("Helllo !!!\n");
    }
  }
}
void display(String temp, String LDR) {

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x = 7; x >= -120; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Temp: " + temp + "C. LDR " + LDR);
    matrix.writeDisplay();
    delay(50);
  }
  matrix.setRotation(0);
}
  void loop() {
    
    if (client.connect(server, 80)) {
      Serial.println("connected");
      client.print((String)(LM.readTemperature()) + " Cx");
      client.print((String)(analogRead(analogInPin)) + " LDRy");
      LM.printOut();
      Serial.println(analogRead(analogInPin));
      delay(1000);
      display(String((int)LM.readTemperature()),String(analogRead(analogInPin)));
    }
  }
