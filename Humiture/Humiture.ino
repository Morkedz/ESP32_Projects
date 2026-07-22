#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

// ==========================================
// 1. NETWORK & SENSOR CONFIGURATION
// ==========================================
const char* SSID         = "wifi";     // Replace with your Wi-Fi name
const char* PASSWORD     = "password"; // Replace with your Wi-Fi password

const char* MQTT_BROKER = "test.mosquitto.org";
const int   MQTT_PORT   = 1883;
const char* MQTT_TOPIC  = "YOUR_TOPIC/humiture"; // Must match MQTT_TOPIC

#define DHTPIN 13           // GPIO pin connected to DHT sensor data pin
#define DHTTYPE DHT22      // Change to DHT11 if using a DHT11 sensor

// ==========================================
// 2. OBJECT INITIALIZATION
// ==========================================
WiFiClient espClient;
PubSubClient mqttClient(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsgTime = 0;
const long publishInterval = 2000; // Publish every 2 seconds

// ==========================================
// 3. HELPER FUNCTIONS
// ==========================================
void setupWiFi() {
  delay(10);
  Serial.print("Connecting to WiFi: ");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected! IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Generate a random client ID for the ESP32
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected to MQTT broker!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// ==========================================
// 4. MAIN SETUP & LOOP
// ==========================================
void setup() {
  Serial.begin(115200);
  dht.begin();
  setupWiFi();
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > publishInterval) {
    lastMsgTime = now;

    // Read sensor data
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Celsius

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Format JSON matching your app.py expectation
    StaticJsonDocument<128> doc;
    doc["temperature"] = round(t * 10.0) / 10.0;
    doc["humidity"]    = round(h * 10.0) / 10.0;

    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer);

    // Publish JSON string to MQTT
    mqttClient.publish(MQTT_TOPIC, jsonBuffer);
    Serial.print("Published to ");
    Serial.print(MQTT_TOPIC);
    Serial.print(": ");
    Serial.println(jsonBuffer);
  }
}