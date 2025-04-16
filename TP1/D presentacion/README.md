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


|  |  |
|--|--|
| 7 . Aplicación → Interacción usuario-red
6 . Presentación → Cifrado/compresión 
5.  Sesión → Gestión de conexiones 
4 . Transporte → Control de flujo/errores
3 . Red → Enrutamiento 
2 . Enlace de datos → Transferencia entre nodos
1 . Física → Transmisión física | ![osi](https://photos.app.goo.gl/AuRRXiwoMpFN7Sv46) |


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
![comunicacion](https://photos.app.goo.gl/1vHDdrzU9dird5yw5)  
*Dispositivo IoT → Gateway → Nube (Plataforma IoT) → Aplicación móvil/web*