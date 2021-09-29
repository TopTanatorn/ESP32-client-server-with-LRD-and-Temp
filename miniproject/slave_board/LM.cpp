#include "Arduino.h"
#include "LM.h"
#include <Wire.h>
#define LM73_ADDR 0x4D
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300       /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

LM::LM(){
}
float LM::readTemperature() {
  Wire1.begin(4, 5);
  Wire1.beginTransmission(LM73_ADDR);
  Wire1.write(0x00); // Temperature Data Register
  Wire1.endTransmission();
  uint8_t count = Wire1.requestFrom(LM73_ADDR, 2);
  float temp = 0.0;
  if (count == 2) {
    byte buff[2];
    buff[0] = Wire1.read();
    buff[1] = Wire1.read();
    temp += (int)(buff[0] << 1);
    if (buff[1] & 0b10000000) temp += 1.0;
    if (buff[1] & 0b01000000) temp += 0.5;
    if (buff[1] & 0b00100000) temp += 0.25;
    if (buff[0] & 0b10000000) temp *= -1.0;
  }
  return temp;
}
void LM::printOut() {
  temp = readTemperature();
  Serial.println("");
  Serial.print("Temp:"); Serial.println(temp);
  delay(1000);
}
void LM::deepSleep() {
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("Wakeup by timmer");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}
