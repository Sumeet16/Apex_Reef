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

```
ESP32
 ├── 8-Channel Relay Module
 ├── PZEM-004T v3.0 (AC Power Meter)
 ├── Wi-Fi
 └── MQTT Broker
       ↓
Home Assistant Dashboard
```

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
```

### Example MQTT Sensor

```yaml
sensor:
  - name: Aquarium Voltage
    state_topic: "home/power_monitor/voltage"
    unit_of_measurement: "V"
```

---

## 💾 Relay State Persistence

Relay states are saved using **ESP32 NVS (Preferences library)**.

✔ Power loss safe  
✔ Automatic restore on reboot  
✔ No accidental device resets  

---

## 🚀 Why This Project

Built to:

- Learn **ESP32 embedded development**
- Integrate **hardware with Home Assistant**
- Measure **real AC power consumption**
- Create a reliable **home & aquarium automation system**
- Combine **IoT, firmware, MQTT, and automation**

---

## 🧩 Tech Stack

- ESP32 (Arduino Framework)
- MQTT (PubSubClient)
- PZEM004Tv30 Library
- Home Assistant
- Mosquitto MQTT Broker
- ESP32 Preferences (NVS)

---

## 📌 Future Improvements

- Add Temperature Sensor
- TLS-secured MQTT
- Improve Power Failure Logic 

---

