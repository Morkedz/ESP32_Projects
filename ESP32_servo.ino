#include <ESP32Servo.h>

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
}

void loop() {
  myServo.write(0);
  delay(1000);

  myServo.write(90);
  delay(1000);

  myServo.write(180);
  delay(1000);

  myServo.write(90);
  delay(1000);
}