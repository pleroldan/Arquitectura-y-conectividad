
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS    15 //d8
#define LORA_RST   0  // d3
#define LORA_DIO0  5  //d1


#define LORA_SCK   14
#define LORA_MISO  12  //
#define LORA_MOSI  13




#define LED_PIN  2 // Puedes cambiar el pin si lo necesitas

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Error al iniciar LoRa receptor.");
    while (true) delay(1000);
    LoRa.dumpRegisters(Serial);
  }

  Serial.println("✅ LoRa receptor listo. Esperando comandos...");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = LoRa.readString();

    Serial.print("📥 Recibido: ");
    Serial.println(message);

    if (message == "LED_ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("💡 LED ENCENDIDO");
    }
    else if (message == "LED_OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("💡 LED APAGADO");
    }
    else {
      Serial.println("⚠️ Comando desconocido");
    }
  }
}