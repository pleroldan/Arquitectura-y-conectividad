#include <SPI.h>
#include <LoRa.h>

// Pines LoRa para ESP32 (ajústalos según tu cableado)
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

void setup() {
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  delay(1000);

  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Error al iniciar LoRa. Verifica conexiones.");
    while (true) delay(1000);
  }

  Serial.println("✅ LoRa listo. Escribe 1 para LED_ON, 2 para LED_OFF:");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == '1') {
      LoRa.beginPacket();
      LoRa.print("LED_ON");
      LoRa.endPacket();
      Serial.println("Enviado: LED_ON");
    }
    else if (cmd == '2') {
      LoRa.beginPacket();
      LoRa.print("LED_OFF");
      LoRa.endPacket();
      Serial.println("Enviado: LED_OFF");
    }
  }
}
