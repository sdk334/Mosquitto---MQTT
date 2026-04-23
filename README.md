# Mosquitto---MQTT
# Instalación y Configuración de Mosquitto MQTT en Raspberry Pi con Publisher ESP32

## Descripción
Este proyecto documenta la implementación de una arquitectura IoT utilizando el protocolo **MQTT**. Se emplea una **Raspberry Pi** como Broker (servidor de mensajería) mediante **Mosquitto** y una **ESP32** como nodo sensor (Publisher) que envía datos simulados de temperatura y humedad.

## Requisitos
* **Hardware:** Raspberry Pi (con Raspberry Pi OS), ESP32 DevKit V1.
* **Software:** Mosquitto Broker, Arduino IDE / PlatformIO.
* **Librerías:** `PubSubClient`, `WiFi.h`.

## Configuración del Broker (Raspberry Pi)
1. **Instalación:**
   sudo apt update && sudo apt upgrade -y
   sudo apt install mosquitto mosquitto-clients -y
