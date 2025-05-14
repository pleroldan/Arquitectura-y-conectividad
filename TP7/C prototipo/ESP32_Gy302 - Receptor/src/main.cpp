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

// Configuración LED y sensor
#define LED_PIN    16
BH1750 lightSensor;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inicialización I2C y BH1750
  Wire.begin();
 // Inicialización CORRECTA:
  if (!lightSensor.begin()) {  // Sin modo de operación
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
  if (millis() - ultimoEnvio > 3000) {  // Envía cada 3 segundos
    float lux = lightSensor.readLightLevel();
    String datos = "LUX=" + String(lux, 1);
    
    LoRa.beginPacket();
    LoRa.print(datos);
    LoRa.endPacket();
    Serial.println("📤 Datos enviados: " + datos);
    ultimoEnvio = millis();
  }
}