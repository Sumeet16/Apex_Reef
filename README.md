🔌 ESP32 Smart Power & Relay Controller (Home Assistant + MQTT)

A Home Assistant–integrated ESP32 smart controller that combines 8-channel relay control with real-time AC power monitoring using the PZEM-004T v3.0 energy meter.

This project allows you to remotely control electrical devices (lights, pumps, heaters, etc.) and monitor voltage, current, power, and energy consumption live inside Home Assistant via MQTT.

✨ Features

✅ 8 Relay Outputs (lights, pumps, heater, skimmer, ATO, air pump, etc.)

📡 MQTT-based control & state feedback

🔁 Relay state persistence (restores last state after power loss)

⚡ Real-time power monitoring

Voltage (V)

Current (A)

Power (W)

Energy (kWh)

🏠 Home Assistant compatible

📊 Ready for Grafana / InfluxDB dashboards

🔐 Secure Wi-Fi + MQTT authentication

🧠 System Architecture
ESP32
 ├── 8-Channel Relay Module
 ├── PZEM-004T v3.0 (AC Power Meter)
 ├── Wi-Fi
 └── MQTT Broker
       ↓
Home Assistant Dashboard

🛠 Hardware Used
Component	Purpose
ESP32 Dev Board	Main controller (Wi-Fi + logic)
8-Channel Relay Module	Switch AC devices ON/OFF
PZEM-004T v3.0	Measure Voltage, Current, Power & Energy
AC Load Devices	Light, pump, heater, skimmer, etc.
MQTT Broker (Mosquitto)	Communication layer
Home Assistant	UI, automation & monitoring
🔌 Relay Mapping
Device	GPIO	MQTT Command Topic	MQTT State Topic
Aquarium Light	GPIO 15	home/aquarium_light/set	home/aquarium_light/state
Pump	GPIO 2	home/pump/set	home/pump/state
Heater	GPIO 4	home/heater/set	home/heater/state
Skimmer	GPIO 5	home/skimmer/set	home/skimmer/state
Light Bulb	GPIO 18	home/light_bulb/set	home/light_bulb/state
ATO Pump	GPIO 19	home/ato_pump/set	home/ato_pump/state
Air Pump	GPIO 21	home/air_pump/set	home/air_pump/state
Extra Socket	GPIO 22	home/extra_socket/set	home/extra_socket/state
⚡ Power Monitoring (PZEM-004T v3.0)

The PZEM-004T v3.0 is connected via UART (Serial2):

Signal	ESP32 Pin
RX	GPIO 16
TX	GPIO 17
Published MQTT Topics
Measurement	MQTT Topic
Voltage	home/power_monitor/voltage
Current	home/power_monitor/current
Power	home/power_monitor/power
Energy	home/power_monitor/energy

All values are published every 5 seconds and retained for Home Assistant restarts.

🏠 Home Assistant Integration

This project works seamlessly with Home Assistant MQTT integration.

Example MQTT Switch Configuration
switch:
  - name: Aquarium Light
    command_topic: "home/aquarium_light/set"
    state_topic: "home/aquarium_light/state"
    payload_on: "ON"
    payload_off: "OFF"
    retain: true

Example MQTT Sensor Configuration
sensor:
  - name: "Aquarium Voltage"
    state_topic: "home/power_monitor/voltage"
    unit_of_measurement: "V"

💾 Relay State Persistence

The ESP32 uses NVS (Preferences library) to store relay states.

✔ If power is lost
✔ ESP32 reboots
✔ All relays restore their last state automatically

No accidental device resets.

🚀 Why I Built This

This project was built to:

Learn embedded systems + IoT

Integrate ESP32 with Home Assistant

Monitor real power usage instead of estimated values

Create a reliable smart control system for aquarium & home automation

Combine hardware, firmware, and home automation in one system

🧩 Tech Stack

ESP32 (Arduino Framework)

MQTT (PubSubClient)

PZEM004Tv30 Library

Home Assistant

Mosquitto MQTT Broker

NVS / Preferences Storage

📌 Future Improvements

🔲 OTA firmware updates

📈 InfluxDB + Grafana dashboards

🧠 Power-based automation rules

🔒 TLS-secured MQTT

📱 Home Assistant Lovelace UI cards

👤 Author

Sumeet Yadav
📍 Canada
💻 Embedded Systems | IoT | Home Assistant | DevOps
🔗 LinkedIn: (add your LinkedIn link here)

⭐ If you like this project

Give it a ⭐ on GitHub and feel free to fork or improve it!

If you want, I can also:

Write your LinkedIn post caption

Create Home Assistant dashboard cards

Add schematics / wiring diagrams

Convert this into a portfolio case study

Just tell me 👍

generate me a readme.md file

Here is the ready-to-use README.md file content.
You can copy-paste this directly into your GitHub repo 👇

# 🔌 ESP32 Smart Power & Relay Controller  
### Home Assistant + MQTT + PZEM-004T v3.0

A **Home Assistant–integrated ESP32 smart controller** that combines **8-channel relay control** with **real-time AC power monitoring** using the **PZEM-004T v3.0** energy meter.

This project allows you to **remotely control electrical devices** (lights, pumps, heaters, etc.) and **monitor voltage, current, power, and energy consumption** live inside **Home Assistant** via **MQTT**.

---

## ✨ Features

- ✅ 8-channel relay control via MQTT  
- 🔁 Relay state persistence (restores state after reboot)  
- ⚡ Real-time AC power monitoring  
  - Voltage (V)  
  - Current (A)  
  - Power (W)  
  - Energy (kWh)  
- 📡 MQTT-based communication  
- 🏠 Fully compatible with Home Assistant  
- 📊 Ready for Grafana / InfluxDB dashboards  
- 🔐 Wi-Fi + MQTT authentication  

---

## 🧠 System Architecture



ESP32
├── 8-Channel Relay Module
├── PZEM-004T v3.0 (AC Power Meter)
├── Wi-Fi
└── MQTT Broker
↓
Home Assistant Dashboard


---

## 🛠 Hardware Used

| Component | Purpose |
|---------|--------|
| ESP32 Dev Board | Main controller with Wi-Fi |
| 8-Channel Relay Module | Switching AC devices |
| PZEM-004T v3.0 | Voltage, current, power & energy measurement |
| AC Loads | Light, pump, heater, skimmer, etc. |
| MQTT Broker (Mosquitto) | Messaging layer |
| Home Assistant | Automation & dashboard |

---

## 🔌 Relay Mapping

| Device | GPIO | MQTT Command Topic | MQTT State Topic |
|------|------|------------------|----------------|
| Aquarium Light | GPIO 15 | `home/aquarium_light/set` | `home/aquarium_light/state` |
| Pump | GPIO 2 | `home/pump/set` | `home/pump/state` |
| Heater | GPIO 4 | `home/heater/set` | `home/heater/state` |
| Skimmer | GPIO 5 | `home/skimmer/set` | `home/skimmer/state` |
| Light Bulb | GPIO 18 | `home/light_bulb/set` | `home/light_bulb/state` |
| ATO Pump | GPIO 19 | `home/ato_pump/set` | `home/ato_pump/state` |
| Air Pump | GPIO 21 | `home/air_pump/set` | `home/air_pump/state` |
| Extra Socket | GPIO 22 | `home/extra_socket/set` | `home/extra_socket/state` |

---

## ⚡ Power Monitoring (PZEM-004T v3.0)

The **PZEM-004T v3.0** is connected to the ESP32 using **UART (Serial2)**.

### UART Wiring

| PZEM | ESP32 |
|----|------|
| TX | GPIO 16 |
| RX | GPIO 17 |

### Published MQTT Topics

| Measurement | MQTT Topic |
|------------|-----------|
| Voltage | `home/power_monitor/voltage` |
| Current | `home/power_monitor/current` |
| Power | `home/power_monitor/power` |
| Energy | `home/power_monitor/energy` |

Values are published every **5 seconds** and retained.

---

## 🏠 Home Assistant Integration

Works seamlessly using the **MQTT integration** in Home Assistant.

### Example MQTT Switch

```yaml
switch:
  - name: Aquarium Light
    command_topic: "home/aquarium_light/set"
    state_topic: "home/aquarium_light/state"
    payload_on: "ON"
    payload_off: "OFF"
    retain: true

Example MQTT Sensor
sensor:
  - name: Aquarium Voltage
    state_topic: "home/power_monitor/voltage"
    unit_of_measurement: "V"

💾 Relay State Persistence

Relay states are saved using ESP32 NVS (Preferences library).

✔ Power loss safe
✔ Automatic restore on reboot
✔ No accidental device resets

🚀 Why This Project

Built to:

Learn ESP32 embedded development

Integrate hardware with Home Assistant

Measure real AC power consumption

Create a reliable home & aquarium automation system

Combine IoT, firmware, MQTT, and automation

🧩 Tech Stack

ESP32 (Arduino Framework)

MQTT (PubSubClient)

PZEM004Tv30 Library

Home Assistant

Mosquitto MQTT Broker

ESP32 Preferences (NVS)

📌 Future Improvements

OTA firmware updates

TLS-secured MQTT

InfluxDB + Grafana integration

Power-based automation rules

Custom Home Assistant Lovelace cards
