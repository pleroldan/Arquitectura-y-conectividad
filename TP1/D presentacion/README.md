# **TECNICATURA SUPERIOR EN Telecomunicaciones**
## ARQUITECTURA Y CONECTIVIDAD 
###  Módulo I: Protocolo de Comunicaciones  

Cuestionario: 

 1.  Nombre, describa y grafique las capas OSI. 
 2.  ¿Cómo se comunican los dispositivos IoT?, Esquematizar y ejemplificar. 
 3. Ejemplifique que son dispositivos IoT 
 4.  ¿Qué tecnologías han hecho posible el IoT menciona 5 ejemplos? 
 5. ¿Qué es la comunicación de datos en serie?, describa su funcionamiento 
 6. ¿Cuáles son los protocolos serie más usados?, nombre 3 y descríbalos. 
 7. ¿Qué es la comunicación de datos en paralelo? Describa su funcionamiento.
 8. ¿Cuáles son los protocolos paralelo más usados?, nombre alguno y descríbalo.
---  
#### **1) Nombre, describa y grafique las capas OSI.**

El modelo OSI (Open Systems Interconnection) es un marco de referencia que divide el proceso de comunicación en redes en siete capas, cada una con funciones específicas:  

| **Capa** | **Nombre** | **Función principal** |
| --- | --- | --- |
| 7 | Aplicación | Interacción con el usuario y servicios de red (ej: HTTP, MQTT). |
| 6 | Presentación | Traducción, cifrado y compresión de datos (ej: SSL/TLS). |
| 5 | Sesión | Control de sesiones y conexiones entre aplicaciones. |
| 4 | Transporte | Entrega confiable de datos, control de errores y segmentación (ej: TCP, UDP). |
| 3 | Red | Direccionamiento y enrutamiento de paquetes (ej: IP, IPv6). |
| 2 | Enlace de datos | Transferencia libre de errores entre nodos conectados (ej: Ethernet, IEEE 802.15.4). |
| 1 | Física | Transmisión de bits a través del medio físico (ej: cables, señales inalámbricas). |



7 . Aplicación → Interacción usuario-red
6 . Presentación → Cifrado/compresión 
5.  Sesión → Gestión de conexiones 
4 . Transporte → Control de flujo/errores
3 . Red → Enrutamiento 
2 . Enlace de datos → Transferencia entre nodos
1 . Física → Transmisión física 

![osi](https://github.com/tpaez/Arquitectura-y-Conectiviad--Grupo2/blob/main/TP1/C%20prototipo/OSI.png) 


---  
#### **2) ¿Cómo se comunican los dispositivos IoT? Esquematizar y ejemplificar.**

Los dispositivos IoT se comunican mediante protocolos inalámbricos o cableados, dependiendo del contexto:  
- **Comunicación directa entre dispositivos**:

    - **Protocolos**: Bluetooth, Zigbee, Z-Wave.
    - **Ejemplo**: Un termostato inteligente envía datos a un sensor de temperatura mediante Zigbee.
- **Comunicación con la nube**:

    - **Protocolos**: MQTT, CoAP, HTTP.
    - **Ejemplo**: Una cámara de seguridad envía imágenes a la nube mediante MQTT.
- **Redes de área amplia (LPWAN)**:

    - **Protocolos**: LoRaWAN, NB-IoT.
    - **Ejemplo**: Sensores agrícolas envían datos de humedad a un servidor central mediante LoRaWAN.  
       
  
    
    
**Esquema:**  
![comunicacion](https://github.com/tpaez/Arquitectura-y-Conectiviad--Grupo2/blob/main/TP1/C%20prototipo/Comunicacion.png)    
*Dispositivo IoT → Gateway → Nube (Plataforma IoT) → Aplicación móvil/web*

---   

#### **3) Ejemplifique qué son dispositivos IoT.**

Los dispositivos IoT son objetos físicos conectados a Internet que recopilan, transmiten y procesan datos.  **Ejemplos**:

- Dispositivos domésticos inteligentes: Termostatos, refrigeradores, televisores, bombillas, cerraduras, detectores de humo.   
- Dispositivos portátiles: Relojes inteligentes, pulseras, zapatillas deportivas con GPS. 
- Sensores: Sensores de humedad para la agricultura, sensores industriales para los automóviles, sensores para medir la calidad del aire. 
- Electrodomésticos inteligentes: Neveras que indican la fecha de caducidad, lavadoras, secadoras.
- Dispositivos de seguridad: Sistemas de seguridad para el hogar, sensores médicos. 
- Dispositivos de automatización: Sistemas de automatización de edificios, sistemas de jardines inteligentes. 
- Dispositivos para la industria: Cascos, exoesqueletos, botas, guantes, gafas Los dispositivos IoT se gestionan a través de interfaces gráficas de usuario (IU), como sitios web o aplicaciones móviles. 



![03-ejemplos](https://github.com/tpaez/Arquitectura-y-Conectiviad--Grupo2/blob/main/TP1/C%20prototipo/03-ejemplos.png)  


 ---

#### **4) ¿Qué tecnologías han hecho posible el IoT? Mencione 5 ejemplos.**
1.  **Protocolos de comunicación**:
        -   MQTT, CoAP (para transmisión eficiente de datos).
   2.  **Redes inalámbricas**:
        -   Wi-Fi, Bluetooth, LoRaWAN, NB-IoT.
3.  **Plataformas en la nube**:
        -   AWS IoT Core, Azure IoT Hub (almacenamiento y análisis de datos).
4.  **Sensores y actuadores**:
        -   Sensores de temperatura, humedad, GPS.
5.  **Tecnologías de bajo consumo**:
        -   Zigbee, Z-Wave (para dispositivos con baterías de larga duración).


---

#### **5) ¿Qué es la comunicación de datos en serie? Describa su funcionamiento.**

La comunicación de datos en serie es un método que **envía y recibe datos un bit a la vez**, a través de un solo canal de comunicación. Es un método común para conectar computadoras y dispositivos periféricos.

-   **Funcionamiento**:
1.  **Conversión de datos paralelo a serie**:
    -   Los datos en un sistema digital suelen manejarse en formato paralelo (ej: un byte = 8 bits en paralelo).
    -   Un  **transceptor serial**  (como un UART) convierte estos datos en una secuencia de bits para su transmisión.
2.  **Transmisión bit a bit**:
    -   Cada bit se envía en orden, generalmente comenzando por el  **bit menos significativo (LSB)**  o el  **bit más significativo (MSB)**, según el protocolo.
3.  **Sincronización**:
    -   **Comunicación síncrona**: Usa una señal de reloj compartida (ej: SPI, I²C).
    -   **Comunicación asíncrona**: No requiere reloj; usa bits de inicio/parada (ej: UART).
4.  **Recepción y reconstrucción**:
    -   El receptor reensambla los bits en el dato original usando la misma convención de orden (LSB/MSB).
    -   Se verifican errores mediante técnicas como  **bits de paridad**  o checksums.   


-   **Características**:
    -   Usa un solo cable y/u opcionalmente tierra y reloj.
    -   Ideal para distancias largas y bajo ancho de banda.
---   

#### **6) ¿Cuáles son los protocolos serie más usados? Nombre 3 y descríbalos.**

Los **Protocolos serie** genéricos mas usados son: 
1.  **UART (Universal Asynchronous Receiver-Transmitter)**:
    -   Asíncrono, sin reloj compartido. Usado en módulos GPS y Bluetooth.
2.  **I²C (Inter-Integrated Circuit)**:
    -   Comunicación maestro-esclavo con dos cables (datos y reloj). Usado en sensores.
3.  **SPI (Serial Peripheral Interface)**:
    -   Síncrono, full-duplex. Usado en pantallas y memorias flash.
Otros protocolos específicos pueden ser:
Modbus, LIN, FlexRay, CAN, RS-232

---  

#### **7) ¿Qué es la comunicación de datos en paralelo? Describa su funcionamiento.**

La **comunicación de datos en paralelo** es un método de transmisión donde **múltiples bits se envían simultáneamente** a través de **canales separados** (generalmente cables o pistas de circuito impreso). A diferencia de la comunicación en serie, esta técnica aprovecha el ancho de banda disponible para lograr velocidades de transferencia más altas, aunque con limitaciones en la distancia y complejidad física.

-   **Funcionamiento**:
    
1.  **Estructura del bus paralelo**:
    
    -   Un bus de datos paralelo típico consta de:
        
        -   **Líneas de datos (N bits)**: Por ejemplo, 8, 16, 32 o 64 líneas para transmitir bits en paralelo.
            
        -   **Líneas de control**: Señales como  _strobe_  (para sincronización),  _acknowledge_  (confirmación) y  _enable_  (habilitación).
            
        -   **Línea de reloj (opcional)**: En sistemas síncronos.
            
2.  **Proceso de transmisión**:
    
    - **Paso 1**: El dispositivo emisor coloca los bits en las líneas de datos.
    - **Paso 2**: Las señales de control (como  _strobe_) indican al receptor que los datos están listos.
    -  **Paso 3**: El receptor captura los datos en todos los canales al mismo tiempo (en el flanco de subida/bajada del reloj o señal de control).
    -**Paso 4**: El receptor envía una señal de  _acknowledge_  para confirmar la recepción.
3.  **Sincronización**:
    -   **Comunicación síncrona**: Usa una señal de reloj compartida para coordinar la transmisión (ej: buses PCI en computadoras).
    -   **Comunicación asíncrona**: Emplea señales de control (_handshaking_) para validar los datos (ej: IEEE 1284 en impresoras).

#### **Características clave**

| **Aspecto** | **Comunicación Paralela** | **Comunicación Serie** |
| --- | --- | --- |
| **Velocidad** | Alta (transfiere N bits por ciclo). | Baja (1 bit por ciclo). |
| **Complejidad** | Requiere múltiples cables y sincronización precisa. | Minimalista (1-2 cables). |
| **Distancia máxima** | Limitada (&lt; 1 metro, por problemas de skew). | Eficiente en largas distancias (km). |
| **Costo** | Alto (por el número de pistas/cables). | Bajo. |
| **Inmunidad al ruido** | Susceptible a interferencias (cross-talk entre líneas). | Más robusta (menos líneas expuestas). |

---


#### **8) ¿Cuáles son los protocolos paralelo más usados? Nombre alguno y descríbalo.**

 **IEEE 1284 (Puerto Paralelo Estándar)**
Es un Protocolo paralelo clásico para conectar periféricos como impresoras y escáneres a computadoras. Usa 8 líneas de datos + 5 líneas de control (Strobe, Busy, Ack, etc.).

**GPIB (General Purpose Interface Bus) / IEEE 488**
Protocolo paralelo usado en instrumentación científica y automatización industrial. Usa 8 líneas de datos + 8 líneas de control (gestión de handshaking).

**Bus PCI (Peripheral Component Interconnect)**
  Protocolo paralelo para conectar tarjetas de expansión en computadoras. Utiliza 32 o 64 líneas de datos + líneas de dirección y control.
 **Bus ISA (Industry Standard Architecture)**
 Es un antiguo estándar para PCs y sistemas industriales.
