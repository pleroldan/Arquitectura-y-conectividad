#include <BluetoothSerial.h>
BluetoothSerial SerialBT;  // Instanciamos el Bluetooth

//=== Definición de pines ===
const int ledVerdePin = 12;
const int ledRojoPin  = 14;
const int potPin = 34;  // Entrada analógica para potenciómetro

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Control");  //  Iniciamos Bluetooth con nombre visible

  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);

  digitalWrite(ledVerdePin, LOW);
  digitalWrite(ledRojoPin, LOW);

  Serial.println("Bluetooth listo: ESP32_Control");
}

void loop() {
  if (!SerialBT.available()) return;

  Serial.println("* Datos recibidos por BT *");

  char cmd = SerialBT.read();
  while (SerialBT.available()) SerialBT.read();  // Limpiar buffer

  Serial.print("Comando recibido: '");
  Serial.print(cmd);
  Serial.println("'");

  switch (cmd) {
    case 'V':
      digitalWrite(ledVerdePin, HIGH);
      Serial.println("→ LED VERDE ENCENDIDO");
      break;

    case 'v':
      digitalWrite(ledVerdePin, LOW);
      Serial.println("→ LED VERDE APAGADO");
      break;

    case 'R':
      digitalWrite(ledRojoPin, HIGH);
      Serial.println("→ LED ROJO ENCENDIDO");
      break;

    case 'r':
      digitalWrite(ledRojoPin, LOW);
      Serial.println("→ LED ROJO APAGADO");
      break;

    case 'P': {
      int valor = analogRead(potPin);
      float voltaje = valor * 3.3 / 4095.0;
      String mensaje = "P: " + String(valor) + " (" + String(voltaje, 2) + " V)";
      SerialBT.println(mensaje);  //  Enviamos el valor a la app
      Serial.println("→ " + mensaje);
      break;
    }

    default:
      Serial.println("!! Comando desconocido");
  }

  Serial.print("Estado LEDs: VERDE=");
  Serial.print(digitalRead(ledVerdePin));
  Serial.print("  ROJO=");
  Serial.println(digitalRead(ledRojoPin));
  Serial.println("---------------------------");
}
