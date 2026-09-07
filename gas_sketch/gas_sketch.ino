#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* WIFI_SSID = WIFI_SSID;
const char* WIFI_PASS = WIFI_PASSWORD;

const char* MQTT_SERVER = SERVER_ADDRESS;
const int   MQTT_PORT   = 1883;
const char* MQTT_TOPIC  = TOPIC_FIELD;
const char* CLIENT_ID   = "ESP32_MQ135_Sensor";

const int MQ135_PIN = 34;

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;
const unsigned long INTERVAL_MS = 5000;

void setupWiFi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    if (client.connect(CLIENT_ID)) {
      Serial.print("Comms Connected");
    } else {
      delay(5000);
    }
  }
}

void readAndPublish() {
  // Read raw analog value (0 - 4095)
  int rawAnalog = analogRead(MQ135_PIN);
  
  float voltage = (rawAnalog / 4095.0) * 3.3;

  JsonDocument doc;
  doc["device_id"] = CLIENT_ID;
  doc["raw_adc"]   = rawAnalog;
  doc["voltage"]   = voltage;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);

  client.publish(MQTT_TOPIC, jsonBuffer);
}

void setup() {
  Serial.begin(115200);
  
  // Configure MQ-135 pin
  pinMode(MQ135_PIN, INPUT);
  
  setupWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > INTERVAL_MS) {
    lastMsgTime = now;
    readAndPublish();
  }
}