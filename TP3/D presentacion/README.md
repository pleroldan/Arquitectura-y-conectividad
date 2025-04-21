# **TECNICATURA SUPERIOR EN Telecomunicaciones**
## ARQUITECTURA Y CONECTIVIDAD 
###  Módulo I: Protocolo de Comunicaciones  

Cuestionario: 

 1.  ¿Cuáles son las Peticiones más comunes en el Protocolo HTTP?, ¿Para qué se usan? Ejemplifique.(Indicar por lo menos 5).
 2.  ¿Cuáles son las principales ventajas de utilizar MQTT en comparación con otros protocolos de comunicación IoT? 
 3. ¿Cómo se maneja la seguridad en MQTT y cuáles son algunas de las mejores prácticas para garantizar la protección de los datos transmitidos a través de esteprotocolo?
 4.  Simular un sensor de temperatura, una luz con dimer, un botón de encendido y apagado mediante Wokwi, Proteus, LabView; etc con ESP32.
 5. Implementar un Prototipo del dispositivo antes mencionado con ESP32 y conectarlo a un Broker mediante Protocolo MQTT, visualizando en Smartphone o Tablet. En su defecto controlar y comunicar 3 dispositivos, sensores y/o actuadores, mediante el protocolo mencionado. Pueden usar Arduino, pero necesitan el módulo de comunicación a internet. El lenguaje de programación es a su elección, Phyton, C++, etc.
 6. Realizar el Dashboard y producir video de funcionamiento y presentación en *.ppt.
 7. Imaginen que tienen una casa inteligente con sensores de temperatura, luces automáticas y una cafetera conectada. ¿Por qué sería conveniente usar el protocolo MQTT para que estos dispositivos se comuniquen entre sí? Mencionen al menos tres características del protocolo que justifiquen su respuesta.
 8. Supongamos que un sensor de movimiento instalado en el pasillo publica un mensaje cuando detecta movimiento. Las luces del pasillo están configuradas para encenderse cuando reciben ese mensaje. Explicar cómo funciona esta comunicación usando el modelo publicador/suscriptor de MQTT, e indicar cuál es el papel del broker.
---  
¿Cuáles son las Peticiones más comunes en el Protocolo HTTP?, ¿Para qué se usan?
Ejemplifique. (Indicar por lo menos 5).
La más comunes son:

**GET**:

Su función es solicitar datos de un recurso de un servidor web.
Ejemplo: se solicita el recurso "index.html" del servidor web www.ejemplo.com.
GET /index.html HTTP/1.1 (versión 1.1 del protocolo HTTP)
Host: www.ejemplo.com

**POST**

Se utiliza para enviar datos a un servidor web, como los datos de un formulario
HTML.
Ejemplo: Enviar un formulario de registro (Los datos se envían al servidor para ser
guardados).
POST /registro HTTP/1.1
Host: www.tiendaonline.com
Content-Type: application/x-www-form-urlencoded
nombre=Ana&email=ana@email.com&clave=123456

 **PUT**
 
se utiliza para actualizar o reemplazar completamente un recurso en un servidor
web.
Ejemplo: Actualizar la información del perfil, Se reemplaza todo el perfil actual con
los nuevos datos.
PUT /perfil HTTP/1.1
Host: www.tiendaonline.com
Content-Type: application/json
{
"nombre": "Ana María",
"email": "ana.nuevo@email.com",
"telefono": "123456789"
}

**PATCH**

Se utiliza para actualizar parcialmente un recurso.
Ejemplo: Cambiar solo el número de teléfono, actualiza solo ese campo en el perfil.
PATCH /perfil HTTP/1.1
Host: www.tiendaonline.com
Content-Type: application/json
{
"telefono": "987654321"
}

**DELETE**

Se utiliza para eliminar un recurso en un servidor web.
Ejemplo: Eliminar mi cuenta, le estoy pidiendo al servidor que borre todos mis
datos.
DELETE /cuenta HTTP/1.1
Host: www.tiendaonline.com
