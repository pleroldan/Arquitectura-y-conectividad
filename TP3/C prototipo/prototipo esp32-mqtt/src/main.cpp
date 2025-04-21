#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <AHT10.h>
#include <BH1750.h>
#include <ArduinoJson.h>

// Configuración WiFi
const char* ssid = "Clarowifi4228";
const char* password = "10052069";

// Configuración MQTT
const char* mqtt_server = "192.168.100.3";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";

// Topic MQTT
const char* env_topic = "sensor/ambiente";
const char* status_topic = "sensor/estado";

// Objetos
WiFiClient espClient;
PubSubClient client(espClient);
AHT10 aht10(AHT10_ADDRESS_0X38);
BH1750 lightMeter;

unsigned long lastMsg = 0;
const unsigned long publishInterval = 30000; // 30 segundos
#define MSG_BUFFER_SIZE (256)
char msg[MSG_BUFFER_SIZE];

// Últimos valores para comparar
float lastTemp = -1000;
float lastHum = -1000;
float lastLux = -1000;

const float deltaTemp = 2.0;
const float deltaHum = 2.0;
const float deltaLux = 2.0;

int mqtt_retries = 0;
const int MAX_MQTT_RETRIES = 10;

void restartWithMessage(const char* reason) {
  Serial.println(reason);
  delay(2000);
  ESP.restart();
}

void setup_wifi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int wifi_attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_attempts++;
    if (wifi_attempts > 20) {
      restartWithMessage("No se pudo conectar a WiFi. Reiniciando...");
    }
  }

  Serial.println("\nWiFi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Conectado al servidor MQTT");
      client.publish(status_topic, "ESP32 conectado");
      mqtt_retries = 0;
    } else {
      Serial.print("Falló, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      mqtt_retries++;
      if (mqtt_retries > MAX_MQTT_RETRIES) {
        restartWithMessage("Demasiados errores de conexión MQTT. Reiniciando...");
      }
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);

  setup_wifi();
  Wire.begin();
  delay(1000);

  if (!aht10.begin()) {
    restartWithMessage("Error al iniciar AHT10");
  }

  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    restartWithMessage("Error al iniciar BH1750");
  }

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  float temp = aht10.readTemperature();
  float hum = aht10.readHumidity();
  float lux = lightMeter.readLightLevel();

  bool sendTemp = abs(temp - lastTemp) >= deltaTemp;
  bool sendHum = abs(hum - lastHum) >= deltaHum;
  bool sendLux = abs(lux - lastLux) >= deltaLux;
  bool timeElapsed = now - lastMsg >= publishInterval;

  if (sendTemp || sendHum || sendLux || timeElapsed) {
    lastMsg = now;
    lastTemp = temp;
    lastHum = hum;
    lastLux = lux;

    StaticJsonDocument<200> doc;
    doc["temperatura"] = temp;
    doc["humedad"] = hum;
    doc["lux"] = lux;

    serializeJson(doc, msg);
    client.publish(env_topic, msg);

    Serial.print("JSON enviado: ");
    Serial.println(msg);
  }
}
