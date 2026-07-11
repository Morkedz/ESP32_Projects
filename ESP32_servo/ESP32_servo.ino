#include <ESP32Servo.h>
#include <WiFi.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// Create a servo object
Servo myServo;

//GPIO for servo signal
const int servoPin = 25;

WiFiServer server(80);

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
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client Connected.");
    String currentLine = "";
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c; // Store the request to analyze it later
        
        if (c == '\n') {
          // If the line is blank, it's the end of the HTTP request
          if (currentLine.length() == 0) {
            
            // --- SERVO CONTROL LOGIC ---
            // Check the incoming request string for specific control URLs
            if (request.indexOf("GET /servo/0") >= 0) {
              myServo.write(0);
              Serial.println("Servo moved to 0°");
            } else if (request.indexOf("GET /servo/90") >= 0) {
              myServo.write(90);
              Serial.println("Servo moved to 90°");
            } else if (request.indexOf("GET /servo/180") >= 0) {
              myServo.write(180);
              Serial.println("Servo moved to 180°");
            }

            // --- SEND HTML INTERFACE TO LAPTOP ---
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println(); // Mandatory blank line after headers

            // HTML Webpage Layout & Styling
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>body { font-family: Arial; text-align: center; margin-top: 50px; }");
            client.println(".button { background-color: #008CBA; border: none; color: white; padding: 16px 32px;");
            client.println("text-decoration: none; font-size: 16px; margin: 4px; cursor: pointer; border-radius: 4px; }</style></head>");
            
            client.println("<body><h1>ESP32 Servo Control Panel</h1>");
            client.println("<p>Select an angle to rotate the MG90S servo:</p>");
            
            // Buttons link to the unique URLs handled by the conditional logic above
            client.println("<a href=\"/servo/0\"><button class=\"button\">0&deg;</button></a>");
            client.println("<a href=\"/servo/90\"><button class=\"button\">90&deg;</button></a>");
            client.println("<a href=\"/servo/180\"><button class=\"button\">180&deg;</button></a>");
            
            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}