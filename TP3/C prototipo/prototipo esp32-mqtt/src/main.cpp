#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <AHT10.h>
#include <BH1750.h>

// Configuración WiFi
const char* ssid = "0101";
const char* password = "12345678";

// Configuración MQTT
const char* mqtt_server = "192.168.199.32";  // IP de tu broker
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";

// Topics MQTT
const char* temp_topic = "sensor/aht10/temperatura";
const char* hum_topic = "sensor/aht10/humedad";
const char* lux_topic = "sensor/bh1750/lux";
const char* status_topic = "sensor/estado";

// Objetos
WiFiClient espClient;
PubSubClient client(espClient);
AHT10 aht10(AHT10_ADDRESS_0X38);
BH1750 lightMeter;

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int mqtt_retries = 0;
const int MAX_MQTT_RETRIES = 10;

void restartWithMessage(const char* reason) {
  Serial.println(reason);
  delay(2000);
  ESP.restart();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  delay(100); // pausa para estabilizar

  int wifi_attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_attempts++;
    if (wifi_attempts > 20) { // 10 segundos
      restartWithMessage("No se pudo conectar a WiFi. Reiniciando...");
    }
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Conectado al servidor MQTT");
      client.publish(status_topic, "Conectado");
      mqtt_retries = 0; // reiniciar el contador si conecta
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

  setup_wifi();          // Conexión WiFi primero
  Wire.begin();          // Iniciar I2C
  delay(1000);           // Esperar estabilización de sensores

  if (!aht10.begin()) {
    restartWithMessage("Error al iniciar AHT10. Reiniciando...");
  }

  delay(500);

  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    restartWithMessage("Error al iniciar BH1750. Reiniciando...");
  }

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    // Leer sensores
    float temp = aht10.readTemperature();
    float hum = aht10.readHumidity();
    float lux = lightMeter.readLightLevel();

    // Publicar datos
    snprintf(msg, MSG_BUFFER_SIZE, "%.2f", temp);
    client.publish(temp_topic, msg);
    
    snprintf(msg, MSG_BUFFER_SIZE, "%.2f", hum);
    client.publish(hum_topic, msg);
    
    snprintf(msg, MSG_BUFFER_SIZE, "%.2f", lux);
    client.publish(lux_topic, msg);

    // Mostrar en consola
    Serial.print("Temp: "); Serial.print(temp); Serial.print("°C");
    Serial.print(" | Hum: "); Serial.print(hum); Serial.print("%");
    Serial.print(" | Lux: "); Serial.print(lux); Serial.println(" lx");
  }
}
