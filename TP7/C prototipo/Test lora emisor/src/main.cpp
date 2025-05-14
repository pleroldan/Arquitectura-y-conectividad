#include <SPI.h>
#include <LoRa.h>

// Pines LoRa ESP32
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

void setup() {
  delay(1000);
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Error al iniciar LoRa en ESP32.");
    while (true) delay(1000);
  }

  Serial.println("✅ LoRa listo. Comandos: 1 = LED_ON, 2 = LED_OFF");
}

void loop() {
  // Envío manual de comandos
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '1') {
      LoRa.beginPacket();
      LoRa.print("LED_ON");
      LoRa.endPacket();
      Serial.println("📤 Enviado: LED_ON");
    } else if (cmd == '2') {
      LoRa.beginPacket();
      LoRa.print("LED_OFF");
      LoRa.endPacket();
      Serial.println("📤 Enviado: LED_OFF");
    } else {
      Serial.println("⚠️ Usa 1 o 2 para controlar LED.");
    }
  }

  // Recepción de datos del ESP8266
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String mensaje = LoRa.readString();
    Serial.print("📡 Sensor recibido: ");
    Serial.println(mensaje);
  }
}
