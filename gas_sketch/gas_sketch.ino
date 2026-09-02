#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* WIFI_SSID = WIFI_SSID;
const char* WIFI_PASS = WIFI_PASSWORD;

const char* MQTT_SERVER = "192.168.1.100";
const int   MQTT_PORT   = 1883;
const char* MQTT_TOPIC  = "sensors/mq135/feed";
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

void setup() {
  Serial.begin(115200);
  
  // Configure MQ-135 pin
  pinMode(MQ135_PIN, INPUT);
  
  setupWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  
}