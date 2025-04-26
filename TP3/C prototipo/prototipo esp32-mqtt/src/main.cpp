#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <AHT10.h>
#include <BH1750.h>
#include <ArduinoJson.h>
#define LED_BUILTIN 2

// Configuración WiFi
const char* ssid = "SSID";
const char* password = "Pass";

// Configuración MQTT
const char* mqtt_server = "144b0f0b708947df835498a9bf10bfb5.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "ispc2025";
const char* mqtt_password = "ispc2025A";

// Topics MQTT
const char* env_topic = "sensor/ambiente";
const char* status_topic = "sensor/estado";  //pendiente de immplementarar
const char* request_topic = "sensor/solicitud"; // Topic para recibir solicitudes

// Objetos
WiFiClientSecure espClient;
PubSubClient client(espClient);
AHT10 aht10(AHT10_ADDRESS_0X38);
BH1750 lightMeter;

#define MSG_BUFFER_SIZE (256)
char msg[MSG_BUFFER_SIZE];

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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en topic: ");
  Serial.println(topic);

  // Verifica si el mensaje es para solicitar datos
  if (strcmp(topic, request_topic) == 0) {
    Serial.println("Solicitud de datos recibida");

    // Prender LED interno
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);

    // Leer sensores
    float temp = aht10.readTemperature();
    float hum = aht10.readHumidity();
    float lux = lightMeter.readLightLevel();

    // Crear JSON
    StaticJsonDocument<256> doc;
    doc["temperatura"] = temp;
    doc["humedad"] = hum;
    doc["lux"] = lux;

    serializeJson(doc, msg);
    client.publish(env_topic, msg);

    Serial.print("Datos enviados: ");
    Serial.println(msg);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Conectado al servidor MQTT");
      client.subscribe(request_topic); // Suscribirse para recibir solicitudes
      client.publish(status_topic, "ESP32 conectado");
    } else {
      Serial.print("Falló, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT); // Configurar el LED
  digitalWrite(LED_BUILTIN, LOW);

  setup_wifi();
  Wire.begin();
  delay(1000);

  if (!aht10.begin()) {
    restartWithMessage("Error al iniciar AHT10");
  }

  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    restartWithMessage("Error al iniciar BH1750");
  }

  espClient.setInsecure(); // No verificación SSL
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
