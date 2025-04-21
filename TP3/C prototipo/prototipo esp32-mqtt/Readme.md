#Prototipo de esp32 como Publisher en MQTT


Este proyecto utiliza un ESP32 para medir **temperatura**, **humedad relativa** y **luminosidad** mediante los sensores **AHT10** y **BH1750**, enviando los datos a un **broker MQTT** a través de una red WiFi.

## 🔧 Componentes

| Componente       | Modelo       | Protocolo | Notas |
|------------------|--------------|-----------|-------|
| Microcontrolador | ESP32        | WiFi, I2C |       |
| Sensor Temp/Hum  | AHT10        | I2C       | Dirección: `0x38` |
| Sensor Luminosidad | BH1750     | I2C       | Dirección por defecto: `0x23` |
| Broker MQTT      | Mosquitto u otro | TCP/IP | Local o remoto |

---  

## Conexiones I2C

Conexión por defecto del ESP32:  
Señal	Pin ESP32  
SDA	GPIO 21  
SCL	GPIO 22  
VCC	3.3V  
GND	GND  

---  
## 🚀 Primer Uso  

```cpp
const char* ssid = "NOMBRE_WIFI";
const char* password = "CONTRASEÑA_WIFI";
const char* mqtt_server = "IP_DEL_BROKER";
```  
   - Subí el código al ESP32.

   - Abrí el monitor serial para verificar el estado del dispositivo.

   - Los valores se publican cada 2 segundos en los siguientes topics MQTT:

Topic	Tipo de dato  
- sensor/aht10/temperatura	Temperatura °C  
- sensor/aht10/humedad	Humedad relativa %  
- sensor/bh1750/lux	Iluminancia (lux)  
- ensor/estado	Estado del ESP32  

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