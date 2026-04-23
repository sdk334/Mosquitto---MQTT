# Mosquitto MQTT — Raspberry Pi + ESP32
Materia: INTERNET DE LAS COSAS|EMBEDDED SYSTEMS
Alumno:	JONATHAN URIEL PAREDES MARTINEZ
grupo: 6CM3
 
![MQTT](https://img.shields.io/badge/Protocol-MQTT-blue) ![Mosquitto](https://img.shields.io/badge/Broker-Mosquitto-orange) ![ESP32](https://img.shields.io/badge/Hardware-ESP32-green) ![Raspberry Pi](https://img.shields.io/badge/Hardware-Raspberry%20Pi-red)

 
Broker MQTT sobre Raspberry Pi con ESP32 como nodo publicador de temperatura y humedad.
 
## Arquitectura
 
```
ESP32 (Publisher)  ──── MQTT :1883 ────►  Raspberry Pi (Mosquitto Broker)
  casa/temperatura                              mosquitto_sub -t "casa/#" -v
  casa/humedad
```
 
## Requisitos
 
**Hardware:** Raspberry Pi con Raspberry Pi OS · ESP32 DevKit V1
 
**Librerías Arduino:** `PubSubClient` · `WiFi.h`
 
## Configuración del Broker (Raspberry Pi)
 
```bash
sudo apt update && sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto
```
 
Crear `/etc/mosquitto/conf.d/external.conf`:
 

listener 1883
allow_anonymous true


## Configuración del Publisher (ESP32)
 
### 1. Instalar el soporte para ESP32 en Arduino IDE
 
En **Archivo → Preferencias**, agregar la siguiente URL en *Gestor de URLs adicionales de tarjetas*:
 
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
 
Luego en **Herramientas → Placa → Gestor de tarjetas**, buscar `esp32` e instalar el paquete de **Espressif Systems**.
 
### 2. Instalar la librería PubSubClient
 
En **Herramientas → Administrar bibliotecas**, buscar `PubSubClient` de **Nick O'Leary** e instalarla.
 
### 3. Configurar credenciales
 
Antes de compilar, editar las siguientes variables en `Codigo_ESP32.ino`:
 
```cpp
const char* ssid     = "NOMBRE_RED";
const char* password = "CONTRASEÑA";
const char* mqtt_server = "192.168.X.X"; // IP de la Raspberry Pi
```
 
### 4. Seleccionar la placa y cargar
 
En **Herramientas → Placa** seleccionar `ESP32 Dev Module`, elegir el puerto COM correspondiente y cargar el sketch.
 

El código en `Codigo_ESP32.ino` se conecta al WiFi local, establece conexión con el broker usando su IP estática y publica cada 10 segundos:
 
| Tópico | Payload |
|--------|---------|
| `casa/temperatura` | float en °C |
| `casa/humedad` | float en % |
 

