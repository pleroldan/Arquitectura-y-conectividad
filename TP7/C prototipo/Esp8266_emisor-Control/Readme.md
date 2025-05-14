# 🎮 Controlador LoRa para LED y Lectura de Luz

Este código permite a un microcontrolador (como ESP32 o ESP8266) **enviar comandos** a otro dispositivo vía **LoRa** para:

- Encender/apagar un pin remotamente (En nuestro ejemplo ese un LED, puede ser un relé)
- Recibir y mostrar la **intensidad de luz** (lux) enviada por el sensor BH1750.

## 🧰 Hardware utilizado

-  ESP8266
- Módulo LoRa (433 MHz)
- Monitor Serial (para enviar comandos)

## 🔌 Conexiones

### LoRa
| Señal     | Pin ESP8266 |
|-----------|-------------|
| SS        | 15 (D8)     |
| RST       | 0  (D3)     |
| DIO0      | 5  (D1)     |
| SCK       | 14 (D5)     |
| MISO      | 12 (D6)     |
| MOSI      | 13 (D7)     |
## ✅ Requisitos

- Bibliotecas: `SPI`, `LoRa`

---

## ⚙️ Funcionamiento

1. Se inicia el módulo LoRa.
2. A través del Monitor Serial:
   - Enviando `1`, se manda el comando `LED_ON`.
   - Enviando `2`, se manda el comando `LED_OFF`.
3. El dispositivo receptor ejecuta la orden y responde con datos de luz.
4. Los datos recibidos (ej. `LUX=123.4`) se procesan y se muestra si el ambiente está **oscuro o iluminado**.

## 📥 Comandos disponibles

- `1` → Enviar comando `LED_ON`
- `2` → Enviar comando `LED_OFF`

## 📡 Ejemplo de salida recibida
```cpp
📡 Datos recibidos -------------------
💡 Luminosidad: 38.7 lx
⚫ Ambiente oscuro
```
