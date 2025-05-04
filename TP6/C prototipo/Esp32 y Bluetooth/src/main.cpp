#include "BluetoothSerial.h"
#include "DHT.h"

BluetoothSerial SerialBT;

#define DHTPIN 4          
#define DHTTYPE DHT11    

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_Bluetooth"); // Nombre para emparejar al Bluetooth
  dht.begin();
  Serial.println("Listo para enviar datos por Bluetooth");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    String mensaje = "Temp: " + String(temp) + "°C | Hum: " + String(hum) + "%";
    SerialBT.println(mensaje);
    Serial.println("Enviado: " + mensaje);
  } else {
    SerialBT.println("Error leyendo del sensor");
  }

  delay(2000);  // Cada 2 segundos
}