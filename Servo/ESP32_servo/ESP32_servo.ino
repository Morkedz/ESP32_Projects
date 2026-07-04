#include <ESP32Servo.h>

// Create a servo object
Servo myServo;

//GPIO for servo signal
const int servoPin = 25;

void setup() {
  WiFi.begin("SSID", "PASSWORD");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myServo.setPeriodHertz(50);

  myServo.attach(servoPin);
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