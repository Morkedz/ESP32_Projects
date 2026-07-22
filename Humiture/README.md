# ESP32 DHT22/DHT11 MQTT Humiture Sensor Firmware

This repository contains the Arduino/ESP32 C++ firmware (`Humiture.ino`) for reading temperature and humidity data from a DHT sensor and publishing the measurements periodically to an MQTT broker in JSON format.

---

## 📌 Features

- **Wi-Fi Connectivity:** Automatic connection and reconnection to Wi-Fi.
- **Sensor Integration:** Reads temperature (°C) and relative humidity (%) using the `DHT` library.
- **JSON Formatting:** Formats sensor payloads using `ArduinoJson` (rounded to 1 decimal place).
- **MQTT Publishing:** Periodically publishes formatted JSON payloads to a configured MQTT topic.
- **Robust Reconnection:** Non-blocking MQTT reconnection loop with dynamic client ID generation.

---

## 🛠️ Hardware Requirements

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **ESP32 Development Board** | 1 | Microcontroller with built-in Wi-Fi |
| **DHT22 or DHT11 Sensor** | 1 | Temperature and humidity sensor |
| **10kΩ Resistor** | 1 | Pull-up resistor for data line (if using bare sensor) |
| **Jumper Wires & Breadboard**| - | Wiring setup |

### Wiring Diagram

| DHT Sensor Pin | ESP32 GPIO Pin |
| :--- | :--- |
| **VCC** | 3.3V / 5V |
| **DATA** | GPIO 13 |
| **GND** | GND |

> **Note:** If using a raw 4-pin DHT22 module, place a 10kΩ pull-up resistor between the VCC and DATA pins. Pre-built 3-pin breakout modules usually have this resistor onboard.

---

## 💻 Software & Library Dependencies

Ensure you have the [Arduino IDE](https://www.arduino.cc/en/software) configured with **ESP32 Board Support**.

Install the following libraries via the Arduino Library Manager (**Sketch** > **Include Library** > **Manage Libraries...**):

1. **PubSubClient** by Nick O'Leary (for MQTT communication)
2. **ArduinoJson** by Benoit Blanchon (v6.x or later)
3. **DHT sensor library** by Adafruit
4. **Adafruit Unified Sensor** by Adafruit (Dependency for DHT library)

---

## 🚀 Setup & Configuration

1. **Clone or Download the Repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git](https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git)

Open the Project:
Open Humiture.ino in the Arduino IDE.

Configure Network & MQTT Parameters:
Update the configuration parameters at the top of Humiture.ino (or use a separate config.h file):

const char* SSID         = "YOUR_WIFI_SSID";
const char* PASSWORD     = "YOUR_WIFI_PASSWORD";

const char* MQTT_BROKER = "test.mosquitto.org";
const int   MQTT_PORT   = 1883;
const char* MQTT_TOPIC  = "YOUR_UNIQUE_TOPIC/humiture";

Select Board & Port:

Go to Tools > Board and select ESP32 Dev Module (or your specific ESP32 board).

Select the correct COM port under Tools > Port.

Upload Firmware:
Click the Upload button in the Arduino IDE.