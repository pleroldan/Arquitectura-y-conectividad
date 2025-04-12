## 04 🔗 Protocolos de Acceso a la Red
Este protocolo permite la conexión física o inalámbrica entre dispositivos. Son la base de la comunicación, como elegir entre hablar, escribir o hacer gestos. Son fundamentales para establecer el canal por el cual se enviarán los datos.  

  Algunos ejemplos pueden ser:

- `Wi-Fi`
- `Ethernet`
- `3G/4G/5G` 
- `Bluetooth` 
- `LoRa` 
- `NB-IoT` 

## 📡 Protocolos de Transmisión
Son los encargados de codificar y estructurar la información que se transmite (a través de las redes mencionadas anteriormente).  
Se divide en dos tipos:

### a) Protocolos Informáticos
Usados para comunicar dispositivos IoT con Internet u otros dispositivos IoT.  

- **MQTT** (Teleoperación de colas de mensajes): modelo de publicación-suscripción, ideal para muchos dispositivos.  

- **CoAP** (Protocolo de aplicación restringido): optimizado para dispositivos con pocos recursos.  

- **HTTP/HTTPS**: clásico de la web, aunque más pesado para IoT.
  
  
  

###  b) Protocolos OT (Operacionales o Industriales):

Usados para la comunicación con equipos industriales. Están más orientados al control que al envío de datos complejos.  

-**Modbus**: muy utilizado en entornos industriales.  

-**IEC102 / IEC104**: para contadores eléctricos.  

-**MBUS**:usado en contadores de agua.  
  
---  




# 06 Tipos de Modulaciones en IoT

Las modulaciones definen cómo se codifican los datos en señales para su transmisión en redes IoT. A continuación, se detallan las principales técnicas:

## 1. **LoRa (Modulación de Espectro Ensanchado - *Spread Spectrum*)**
- **Protocolo asociado**: LoRaWAN.
- **Características**:
  - Largo alcance y bajo consumo energético.
  - **Spreading Factor (SF)**: Parámetro ajustable (`SF7` a `SF12`).
    - Mayor SF = Mayor alcance pero menor velocidad de transmisión.
- **Ejemplo**: SF7 con envíos cada 10 minutos ≈ 3 años de vida útil de batería (según tabla del documento).

## 2. **Zigbee (IEEE 802.15.4)**
- **Bandas de frecuencia**: 2.4 GHz, 868 MHz (Europa), 915 MHz (EE.UU.).
- **Modulación**: 
  - **DSSS** (*Direct Sequence Spread Spectrum*).
  - **O-QPSK** (*Offset Quadrature Phase-Shift Keying*) para bajo consumo.
- **Uso típico**: Domótica (ej. Philips Hue, iluminación inteligente).

## 3. **NB-IoT (*Frequency Division Multiple Access - FDMA*)**
- **Enfoque**: Divide el espectro en sub-bandas estrechas.
- **Ventajas**:
  - Alta eficiencia energética.
  - Cobertura en interiores/zonas subterráneas (ej. medidores inteligentes).
- **Velocidad**: Hasta 127 kbps (versión 14 de 3GPP).

## 4. **Otras Modulaciones Comunes**
- **FSK** (*Frequency-Shift Keying*):
  - Usada en protocolos como **Sigfox**.
  - Simple y robusta para distancias cortas.
- **O-QPSK** (*Offset Quadrature Phase-Shift Keying*):
  - Variante de QPSK con menor consumo (empleada en Zigbee).

---  

---  

---


### Comparativa Rápida
| Tecnología     | Modulación                  | Alcance  | Consumo | Aplicación típica         |
|---------------|----------------------------|----------|---------|---------------------------|
| **LoRa**      | Spread Spectrum (SF7-SF12) | Largo    | Muy bajo| Agricultura, ciudades     |
| **Zigbee**    | DSSS / O-QPSK              | Corto    | Bajo    | Domótica, redes mesh      |
| **NB-IoT**    | FDMA                       | Medio    | Bajo    | Medidores, subterráneos   |
| **FSK**       | FSK                        | Corto    | Medio   | Sensores simple
