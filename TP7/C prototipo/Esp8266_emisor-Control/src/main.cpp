#include <SPI.h>
#include <LoRa.h>

// Pines LoRa
#define LORA_SS    15  // D8
#define LORA_RST   0   // D3
#define LORA_DIO0  5   // D1
#define LORA_SCK   14  // D5
#define LORA_MISO  12  // D6
#define LORA_MOSI  13  // D7

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Inicialización LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Fallo al iniciar LoRa");
    while (true);
  }
  Serial.println("✅ LoRa listo. Envia comandos:");
  Serial.println("1: Encender LED");
  Serial.println("2: Apagar LED");
}

void loop() {
  // Envío de comandos LED
  if (Serial.available()) {
    char comando = Serial.read();
    if (comando == '1') {
      LoRa.beginPacket();
      LoRa.print("LED_ON");
      LoRa.endPacket();
      Serial.println("📤 Enviado: LED_ON");
    } 
    else if (comando == '2') {
      LoRa.beginPacket();
      LoRa.print("LED_OFF");
      LoRa.endPacket();
      Serial.println("📤 Enviado: LED_OFF");
    }
  }

  // Recepción de datos de luminosidad
  if (LoRa.parsePacket()) {
    String datos = LoRa.readString();
    Serial.println("\n📡 Datos recibidos -------------------");
    
    // Procesamiento de datos (ej: "LUX=125.5")
    if (datos.startsWith("LUX=")) {
      float lux = datos.substring(4).toFloat();
      Serial.print("💡 Luminosidad: ");
      Serial.print(lux);
      Serial.println(" lx");
      
      // Opcional: Tomar decisiones basadas en la luz
      if (lux < 50) {
        Serial.println("⚫ Ambiente oscuro");
      } else {
        Serial.println("⚪ Ambiente iluminado");
      }
    }
    Serial.println("-----------------------------------");
  }
  delay(100);
}