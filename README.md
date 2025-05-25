# Arquitectura-y-Conectiviad
![image](https://github.com/user-attachments/assets/e4e23b19-34c0-4010-a98c-fc7c4393c38f)


### Profesor: Ing. Jorge Elías Morales.
##

### Grupo N° 2:

- Huk, Romina vanesa - [GitHub: RoHu17](https://github.com/RoHu17)
- Brizuela, Laura Analia - [GitHub: gerbena03](https://github.com/gerbena03)
- Roldán, Patricio Leandro -  [GitHub: pleroldan](https://github.com/pleroldan)
- Pantoja, Paola Natalia Alejandra - [GitHub: PaolaaPantoja](https://github.com/PaolaaPantoja)
- Paez, Tiziano Adrian - [GitHub: tpaez](https://github.com/tpaez)
- Paz, Rodolfo: [GitHub: Domi74](https://github.com/Domi74)
- Gutiérrez, Emma: [GitHub: Emygut ](https://github.com/Emygut)




---  

Proxima actualizacion.
Lora + mqtt + control:

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>
#include <time.h>
#include <ArduinoJson.h>

// Configuración WiFi
const char* ssid = "SSSID";
const char* password = "PASS";

// Configuración MQTT
const char* mqtt_server = "broker";
const int mqtt_port = 0000;
const char* mqtt_user = "Ussr";
const char* mqtt_password = "Pass";

// Topics MQTT
const char* data_topic = "sistema/luz/ambiente";
const char* control_topic = "sistema/luz/control";
const char* status_topic = "sistema/luz/estado";
const char* lora_topic = "sistema/luz/lora";  // Nuevo tópico para calidad de señal LoRa

// Pines LoRa
#define LORA_SS    15
#define LORA_RST   0
#define LORA_DIO0  5

// Pin para el LED del ESP8266
#define LED_REMOTO_PIN 2  // Equivalente a D4

// Objetos para WiFi y MQTT
WiFiClientSecure espClient;
PubSubClient client(espClient);

// Variables de estado
float lux = 0.0;
int luzAmbientePorc = 0;
bool luzRefuerzo = false;
bool modoForzado = false;
unsigned long ultimoComando = 0;

#define MSG_BUFFER_SIZE (256)
char msg[MSG_BUFFER_SIZE];

// Declaraciones adelantadas de funciones
void restartWithMessage(const char* reason);
void setup_wifi();
void enviarDatos();
void evaluarCalidadLoRa();
String getTimestamp();
void reconnect();

// Reinicia el ESP8266 mostrando el mensaje de error
void restartWithMessage(const char* reason) {
  Serial.println(reason);
  delay(2000);
  ESP.restart();
}

// Conexión a WiFi
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

// Obtener timestamp formateado
String getTimestamp() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buf[25];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
  return String(buf);
}

// Enviar datos de iluminación y estado vía MQTT
void enviarDatos() {
  String timestamp = getTimestamp();
  StaticJsonDocument<256> doc;

  doc["timestamp"] = timestamp;
  doc["lux"] = lux;
  doc["porcentaje"] = luzAmbientePorc;
  doc["estado_luz"] = luzRefuerzo ? "on" : "off";
  doc["modo"] = modoForzado ? "forzado" : "automatico";
  doc["rssi_wifi"] = WiFi.RSSI();
  doc["rssi_lora"] = LoRa.packetRssi();

  serializeJson(doc, msg);
  client.publish(data_topic, msg);

  Serial.print("Datos enviados: ");
  Serial.println(msg);
}

// Evaluar calidad de la señal LoRa y enviarla vía MQTT
void evaluarCalidadLoRa() {
  int rssi_lora = LoRa.packetRssi();
  float snr_lora = LoRa.packetSnr();

  StaticJsonDocument<128> doc;
  doc["rssi_lora"] = rssi_lora;
  doc["snr_lora"] = snr_lora;
  doc["estado"] = (rssi_lora > -110 && snr_lora > 0) ? "Buena" : "Deficiente";

  serializeJson(doc, msg);
  client.publish(lora_topic, msg);

  Serial.print("Calidad de LoRa enviada: ");
  Serial.println(msg);
}

// Función de callback para procesar mensajes MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en topic: ");
  Serial.println(topic);

  // Convertir payload a String
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (strcmp(topic, control_topic) == 0) {
    if (message.equalsIgnoreCase("ON")) {
      LoRa.beginPacket();
      LoRa.print("LED_ON");
      LoRa.endPacket();
      luzRefuerzo = true;
      modoForzado = true;
      ultimoComando = millis();
      Serial.println("Comando ON recibido y reenviado a ESP32");
    } 
    else if (message.equalsIgnoreCase("OFF")) {
      LoRa.beginPacket();
      LoRa.print("LED_OFF");
      LoRa.endPacket();
      luzRefuerzo = false;
      modoForzado = true;
      ultimoComando = millis();
      Serial.println("Comando OFF recibido y reenviado a ESP32");
    }
    else if (message.equalsIgnoreCase("AUTO")) {
      modoForzado = false;
      ultimoComando = millis();
      Serial.println("Comando AUTO recibido");
    }
    digitalWrite(LED_REMOTO_PIN, luzRefuerzo ? HIGH : LOW);
    enviarDatos();
  }
}

// Reconexión al broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Conectado al servidor MQTT");
      client.subscribe(control_topic);
      client.publish(status_topic, "ESP8266 conectado");
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
  pinMode(LED_REMOTO_PIN, OUTPUT);
  digitalWrite(LED_REMOTO_PIN, LOW);

  setup_wifi();
  
  configTime(0, 0, "pool.ntp.org");
  Serial.println("Obteniendo hora...");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nHora configurada");

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    restartWithMessage("Error al iniciar LoRa");
  }
  Serial.println("LoRa iniciado correctamente");

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (LoRa.parsePacket()) {
    String datos = LoRa.readString();
    if (datos.startsWith("LUX=")) {
      lux = datos.substring(4).toFloat();
      luzAmbientePorc = constrain(map(lux, 0, 500, 0, 100), 0, 100);

      if (!modoForzado) {
        luzRefuerzo = (lux < 50);
        digitalWrite(LED_REMOTO_PIN, luzRefuerzo ? HIGH : LOW);
      }

      enviarDatos();
      evaluarCalidadLoRa();  // Llamar evaluación de calidad LoRa
    }
  }

  if (modoForzado && millis() - ultimoComando > 60000) {
    modoForzado = false;
    Serial.println("Volviendo a modo automático por inactividad");
  }

  delay(100);
}
