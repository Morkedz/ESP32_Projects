# ESP32 Projects & Hardware Sandbox

A structured collection of standalone ESP32 firmware sketches, sensor diagnostics, and hardware integration tests. 

Each directory contains a distinct, self-contained project focused on a specific hardware component, protocol, or peripheral test.

## Repository Structure

| Directory | Core Focus | Key Hardware & Protocols |
| :--- | :--- | :--- |
| **BMP280_Diagnostic_Script** | I2C bus scanner and BMP280 atmospheric sensor test. | BMP280, I2C (GPIO 21/22), Serial Debug |
| **ESP32_servo** | Web-hosted HTTP dashboard for remote motor control. | MG90S Servo, Wi-Fi Server, HTTP GET |
| **Humiture** | Real-time environmental telemetry publishing. | DHT22 / DHT11, Wi-Fi, MQTT, ArduinoJson |
| **MOSFET_Test** | High/low-side electronic switch gate pulse test. | N-Channel / P-Channel MOSFET, GPIO 18 |
| **Transducer** | External 16-bit ADC voltage reading for pressure sensors. | ADS1115 ADC, Pressure Transducer, I2C |
| **gas_sketch** | Analog gas sensing and JSON telemetry generation. | MQ-135 Gas Sensor, ESP32 ADC (GPIO 34), MQTT |

---

## Getting Started

1. Navigate to the project directory of interest.
2. Ensure you have installed the required libraries listed in that project's sub-README.
3. Open the `.ino` sketch in **Arduino IDE** or **PlatformIO**.
4. Configure target network credentials in `secrets.h` or configuration headers where applicable.
5. Upload to your target ESP32 module.