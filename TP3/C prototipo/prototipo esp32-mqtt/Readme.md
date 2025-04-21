# Prototipo de ESP32 como Publisher en MQTT

Este proyecto utiliza un ESP32 para medir **temperatura**, **humedad relativa** y **luminosidad** mediante los sensores **AHT10** y **BH1750**, enviando los datos a un **broker MQTT** a través de una red WiFi.

---

## 🔧 Componentes

| Componente         | Modelo       | Protocolo | Notas                       |
|--------------------|--------------|-----------|-----------------------------|
| Microcontrolador   | ESP32        | WiFi, I2C |                             |
| Sensor Temp/Hum    | AHT10        | I2C       | Dirección: `0x38`           |
| Sensor Luminosidad | BH1750       | I2C       | Dirección por defecto: `0x23` |
| Broker MQTT        | Mosquitto u otro | TCP/IP | Local o remoto         |

---

## 🔌 Conexiones I2C

Conexión por defecto del ESP32:

| Señal | Pin ESP32 |
|-------|-----------|
| SDA   | GPIO 21   |
| SCL   | GPIO 22   |
| VCC   | 3.3V      |
| GND   | GND       |

---

## 🚀 Primer Uso  

Modificar las siguientes variables en el código:

```cpp
const char* ssid = "NOMBRE_WIFI";
const char* password = "CONTRASEÑA_WIFI";
const char* mqtt_server = "IP_DEL_BROKER";

```  
   - Subí el código al ESP32.

   - Abrí el monitor serial para verificar el estado del dispositivo.

   - Los valores se publican cada 30 segundos en los siguientes topics MQTT:

Topic	Tipo de dato  
- sensor/aht10/temperatura	Temperatura °C  
- sensor/aht10/humedad	Humedad relativa %  
- sensor/bh1750/lux	Iluminancia (lux)  
- ensor/estado	Estado del ESP32  

🆕 Versión 2 (optimización de envío)

Se implementó una lógica para evitar el envío innecesario de datos.
El ESP32 publicará los valores solo si:

    - Pasaron más de 30 segundos desde el último envío.

    - Ocurrió una variación significativa respecto al último dato enviado:

|Variable	|Umbral de cambio|  
|-------|-----------|
|Temperatura	   | ±2 °C  |
|Humedad	   | ±2 %  |
|Luminosidad	|    ±2 lux   | 

El topic **sensor/ambiente** se puede visualizar fácilmente con un cliente MQTT como MyMQTT (Android) o MQTT Explorer.

---  

## 🛠️ Configuración básica de Mosquitto (mosquitto.conf)  

#### Archivo de configuración para Mosquitto
```  
listener 1883 0.0.0.0
allow_anonymous true
```  

#### 📍 Ruta común del archivo de configuración:

En Linux (como Manjaro o Ubuntu):  
    /etc/mosquitto/mosquitto.conf

En Windows (con Mosquitto instalado manualmente):  
    Suele estar en la misma carpeta del ejecutable, por ejemplo:  
    C:\mosquitto\mosquitto.conf  

#### 🚀 Cómo ejecutar Mosquitto con esta config  

En Linux:
```
sudo systemctl stop mosquitto
sudo mosquitto -c /etc/mosquitto/mosquitto.conf
```

En Windows (cmd o PowerShell):
```
mosquitto -v -c "C:\ruta\a\mosquitto.conf"
```