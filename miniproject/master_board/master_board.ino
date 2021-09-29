#include <WiFi.h>
#include "time.h"
const char* ssid     = "Buzzlightyear";
const char* password = "@Top12345";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 6;
const int   daylightOffset_sec = 3600;
WiFiServer server(80);
void setup() {
  // initialize serial:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.print("Connected to wifi. My address:");
  IPAddress myAddress = WiFi.localIP();
  Serial.println(myAddress);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}
void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%H:%M");
}
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             
    Serial.println("New client");
    String currentLine1 = "";
    String currentLine2 = "";
    currentLine1 = client.readStringUntil('x');
    currentLine2 = client.readStringUntil('y');
    Serial.println(currentLine1);
    Serial.println(currentLine2);
    printLocalTime();
  }
}
