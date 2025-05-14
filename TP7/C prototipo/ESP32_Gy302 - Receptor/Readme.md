# 📡 Proyecto ESP32 con LoRa y Sensor de Luz (BH1750)

Este proyecto utiliza un ESP32 para:

- Controlar un **LED** remotamente mediante comandos LoRa.
- Medir la **intensidad de luz** (lux) con un sensor BH1750 (GY-302).
- Transmitir los datos por **LoRa** cada 3 segundos.

## 🧰 Hardware utilizado

- ESP32
- Módulo LoRa (433 MHz)
- Sensor de luz BH1750 (GY-302)
- LED conectado al pin 16

## 🔌 Conexiones

### LoRa
| Señal     | Pin ESP32 |
|-----------|-----------|
| SS        | 5         |
| RST       | 14        |
| DIO0      | 2         |
| SCK       | 18        |
| MISO      | 19        |
| MOSI      | 23        |

### Sensor BH1750
- Conexión I2C (SDA/SCL según ESP32)

## ⚙️ Funcionamiento

1. Se inicializan el sensor BH1750 y el módulo LoRa.
2. En el bucle principal:
   - Si se recibe un comando LoRa (`LED_ON` o `LED_OFF`), enciende o apaga el LED.
   - Cada 3 segundos, lee el valor de luz en lux y lo envía por LoRa.

## 📥 Comandos disponibles

- `LED_ON` → Enciende el LED
- `LED_OFF` → Apaga el LED

## 📤 Formato de datos enviados

LUX=123.4




  
Donde `123.4` es el valor actual de luminosidad medida.

## ✅ Requisitos

- Bibliotecas: `SPI`, `LoRa`, `Wire`, `BH1750`

---

