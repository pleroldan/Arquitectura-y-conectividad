#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

Adafruit_AHTX0 aht;

// UUIDs personalizados
#define SERVICE_UUID           "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID    "abcd1234-5678-90ab-cdef-1234567890ab"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Clase para gestionar eventos del servidor BLE
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Inicializa sensor AHT10
  if (!aht.begin()) {
    Serial.println("No se encontró el sensor AHT10, revisa conexión I2C");
    while (1) delay(10);
  }

  // Inicializa BLE
  BLEDevice::init("ESP32-AHT10");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  pServer->getAdvertising()->start();

  Serial.println("Bluetooth listo, esperando conexión...");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // Leer sensor

  if (deviceConnected) {
    // Formato con etiquetas
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Temp:%.1f;Hum:%.1f", temp.temperature, humidity.relative_humidity);

    pCharacteristic->setValue((uint8_t*)buffer, strlen(buffer));
    pCharacteristic->notify();  // Notificar al cliente

    Serial.print("Enviado por BLE: ");
    Serial.println(buffer);
  }

  delay(2000); // Espera 2 segundos entre mediciones
}
