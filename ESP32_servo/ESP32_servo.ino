#include <ESP32Servo.h>
#include <Wifi.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// Create a servo object
Servo myServo;

//GPIO for servo signal
const int servoPin = 25;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myServo.setPeriodHertz(50);

  myServo.attach(servoPin);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Searching...");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  for(int i = 0; i<181; i+=5){
    myServo.write(i);
    delay(60);
  }
  for(int j=180; j>0; j-=5){
    myServo.write(j);
    delay(60);
  }
}