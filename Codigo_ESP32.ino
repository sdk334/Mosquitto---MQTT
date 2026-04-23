#include <WiFi.h>
#include <PubSubClient.h>

// --- Configuración de Red ---
const char* ssid = "Cuarto_M";
const char* password = "internet";

// --- Configuración del Broker Mosquitto ---
// Sustituir con la IP estática de su Raspberry Pi
const char* mqtt_server = "192.168.1.109"; 

// --- Tópicos ---
const char* topic_temp = "casa/temperatura";
const char* topic_hum = "casa/humedad";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println("\nIniciando conexión WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado correctamente.");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    // ID de cliente 
    if (client.connect("ESP32_Sensor_Sim")) {
      Serial.println("conectado.");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  // Publicar cada 10 segundos
  if (now - lastMsg > 10000) {
    lastMsg = now;

    // Generación de valores aleatorios (Simulación)
    float temperatura = random(200, 350) / 10.0; // 20.0 a 35.0 °C
    float humedad = random(400, 700) / 10.0;     // 40.0 a 70.0 %

    // Conversión y publicación de Temperatura
    char tempString[8];
    dtostrf(temperatura, 1, 2, tempString);
    Serial.print("Publicando Temperatura: ");
    Serial.println(tempString);
    client.publish(topic_temp, tempString);

    // Conversión y publicación de Humedad
    char humString[8];
    dtostrf(humedad, 1, 2, humString);
    Serial.print("Publicando Humedad: ");
    Serial.println(humString);
    client.publish(topic_hum, humString);
  }
}
