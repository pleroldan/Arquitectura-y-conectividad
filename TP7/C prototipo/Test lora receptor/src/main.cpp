#include <SPI.h>
#include <LoRa.h>

// Pines del LoRa para NodeMCU v3
#define LORA_SS    15  // D8
#define LORA_RST   0   // D3
#define LORA_DIO0  5   // D1

#define LED_PIN    2   // D4 (GPIO2)

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // LED apagado al iniciar  
  delay(1000);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Error al iniciar LoRa.");
    while (true) delay(1000);
  }

  Serial.println("✅ Receptor LoRa listo. Esperando comandos...");
}

void loop() {
  if (LoRa.parsePacket()) {
    char command[16] = {0};
    int i = 0;
    while (LoRa.available() && i < sizeof(command) - 1) {
      command[i++] = LoRa.read();
    }

    Serial.print("Comando recibido: ");
    Serial.println(command);

    if (strcmp(command, "LED_ON") == 0) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("💡 LED encendido (D4)");
    } else if (strcmp(command, "LED_OFF") == 0) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("💡 LED apagado (D4)");
    }
  }
}
