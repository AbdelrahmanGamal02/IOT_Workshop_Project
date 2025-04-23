# 📡 IoT Workshop Project: LED & IR Sensor Control via MQTT

This project demonstrates how to use **IoT concepts** and the **MQTT protocol** to control an LED and monitor an IR sensor using the **ESP8266 microcontroller**. Communication is established between the ESP8266 and a mobile phone through the **IoT MQTT Panel** application.

---

## 🧾 Project Specifications

- **Microcontroller**: ESP8266 (e.g., NodeMCU)
- **Communication Protocol**: MQTT
- **Broker**: [broker.emqx.io](https://www.emqx.io/), Port: `1883`
- **Mobile Application**: IoT MQTT Panel (Android)
- **Functions**:
  - Publish IR sensor status to mobile
  - Control an LED from the mobile phone using MQTT

---

## 🛠️ Project Steps

### ⚙️ Setup Function (`setup()`)

1. **WiFi Initialization**
   ```cpp
   WiFi.begin("Your_SSID", "Your_PASSWORD");  // Case-sensitive
2. **MQTT Broker Connection**
   Create MQTT client instance:
   ```cpp
   WiFiClient espClient;
   PubSubClient client(espClient);
3. **Set MQTT broker server:**
   ```cpp
   client.setServer("broker.emqx.io", 1883);

4. **Subscribe to Topic**
   ```cpp
   client.subscribe("iot/led");

5. **Set Callback Function**
   ```cpp
   client.setCallback(callbackFunction);

6. **Define Callback Function**
   ```cpp
   void callbackFunction(char* topic, byte* payload, unsigned int length) {
    // Handle received data
   }

### ⚙️ Loop  Function (`Loop ()`)

1. **Publish IR Sensor Status**
   ```cpp
   client.publish("Your Topic" , "Your Message");

2. **Control LED Based on Message**



## 📚 Required Libraries

Make sure to install the following libraries in your Arduino IDE before uploading the code to your ESP8266:

1. **ESP8266WiFi.h**  
   - Handles WiFi connectivity for the ESP8266.
   - Available by default when using the ESP8266 board package in Arduino IDE.

2. **PubSubClient.h**  
   - Handles MQTT communication (publish/subscribe).
   - Install via Library Manager

**How to Install Libraries**:
- Open Arduino IDE.
- Go to `Sketch` → `Include Library` → `Manage Libraries...`
- Search for the library name and click **Install**.

---

## 📱 IoT MQTT Panel App Setup

To control and monitor your IoT device, use the **IoT MQTT Panel** Android app:

1. **Download the App**  
   - Available on Google Play: [IoT MQTT Panel](https://play.google.com/store/apps/details?id=com.rmqtt.iot)

2. **Add a New MQTT Connection**  
   - Broker: `broker.emqx.io`
   - Port: `1883`
   - Client ID: (any unique name, e.g., `esp8266-client`)
   - Keep Alive: Default (60 seconds)
     
3. **Add Widgets**:
   - **Switch Widget**
     - Topic: `iot/led`
     - Type: Publish
     - Payload: `"ON"` / `"OFF"` to control the LED

   - **LED Indecator**
     - Topic: `iot/ir`
     - Type: Subscribe
     - This will use Led to display real-time status from the IR sensor (e.g., "Detected", "Clear")

**Tips**:
- Ensure your phone and ESP8266 are connected to the internet.
- Use simple topic names to avoid typos.

---

## Summary

This project illustrates a basic yet effective IoT application using MQTT and ESP8266. It helps you learn:

- How to use MQTT for IoT communication
- How to control GPIO devices remotely
- How to send sensor data to a mobile app in real time

🔗 Ideal for students and hobbyists learning IoT, embedded systems, and wireless communication.

