#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <BH1750.h>  // Biblioteca para el GY-302

// Pines LoRa
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23

// Pines LED
#define LED_PIN       16  // Controlado por comandos
#define LIGHT_LED_PIN 17  // Se enciende si está oscuro

BH1750 lightSensor;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(LIGHT_LED_PIN, OUTPUT);
  digitalWrite(LIGHT_LED_PIN, LOW);

  // Inicialización I2C y BH1750
  Wire.begin();
  if (!lightSensor.begin()) {
    Serial.println("❌ Fallo al iniciar BH1750");
    while (true);
  }
  Serial.println("✅ BH1750 iniciado");

  // Inicialización LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("❌ Fallo al iniciar LoRa. Revisa los pines.");
    while (true);
  }
  Serial.println("✅ LoRa iniciado. Esperando comandos...");
}

void loop() {
  // Recepción de comandos LED
  if (LoRa.parsePacket()) {
    String comando = LoRa.readString();
    Serial.print("📥 Comando recibido: ");
    Serial.println(comando);

    if (comando == "LED_ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("💡 LED encendido");
    } 
    else if (comando == "LED_OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("💡 LED apagado");
    }
  }

  // Lectura y envío de luminosidad
  static unsigned long ultimoEnvio = 0;
  if (millis() - ultimoEnvio > 3000) {
    float lux = lightSensor.readLightLevel();
    String datos = "LUX=" + String(lux, 1);

    // Envío por LoRa
    LoRa.beginPacket();
    LoRa.print(datos);
    LoRa.endPacket();
    Serial.println("📤 Datos enviados: " + datos);

    // Control del LED según luminosidad
    if (lux < 50) {
      digitalWrite(LIGHT_LED_PIN, HIGH);
      Serial.println("🌑 Ambiente oscuro → LED ambiental encendido");
    } else {
      digitalWrite(LIGHT_LED_PIN, LOW);
      Serial.println("☀️ Ambiente iluminado → LED ambiental apagado");
    }

    ultimoEnvio = millis();
  }
}
