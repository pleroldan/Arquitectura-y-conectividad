#include <Arduino.h>
#include <Wire.h>
#include <AHT10.h>

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nEscaneando I2C...");
  for (byte addr = 0; addr <= 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo en: 0x");
      Serial.println(addr, HEX);
    }
  }
}

void loop() {}