# Mosquitto MQTT — Raspberry Pi + ESP32
 
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

 
## Publisher (ESP32)
 
El código en `src/` se conecta al WiFi local, establece conexión con el broker usando su IP estática y publica cada 10 segundos:
 
| Tópico | Payload |
|--------|---------|
| `casa/temperatura` | float en °C |
| `casa/humedad` | float en % |
 

