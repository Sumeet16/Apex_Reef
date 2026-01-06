#include <WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>
#include <Preferences.h>

// -------------------- PZEM004T Setup --------------------
#define RXD2 16
#define TXD2 17
PZEM004Tv30 pzem(Serial2, RXD2, TXD2);

// -------------------- Wi-Fi Credentials --------------------
const char* ssid = "Wi-Fi_SSID";
const char* password = "Wi-Fi_Password";

// -------------------- MQTT Broker --------------------
const char* mqtt_server = "192.168.2.112";
const int mqtt_port = 1883;
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "mqtt_password";

WiFiClient espClient;
PubSubClient client(espClient);
Preferences preferences;  // for saving relay states

// -------------------- Relay Setup --------------------
struct RelayDevice {
  const char* name;
  const char* commandTopic;
  const char* stateTopic;
  uint8_t pin;
  bool state;
};

RelayDevice relays[] = {
  {"Aquarium Light", "home/aquarium_light/set", "home/aquarium_light/state", 15, false},
  {"Pump",           "home/pump/set",           "home/pump/state",           2,  false},
  {"Heater",         "home/heater/set",         "home/heater/state",         4,  false},
  {"Skimmer",        "home/skimmer/set",        "home/skimmer/state",        5,  false},
  {"Light Bulb",     "home/light_bulb/set",     "home/light_bulb/state",     18, false},
  {"ATO Pump",       "home/ato_pump/set",       "home/ato_pump/state",       19, false},
  {"Air Pump",       "home/air_pump/set",       "home/air_pump/state",       21, false},
  {"Extra Socket",   "home/extra_socket/set",   "home/extra_socket/state",   22, false}
};
const int relayCount = sizeof(relays) / sizeof(relays[0]);

// MQTT topics for power monitoring
const char* topic_voltage = "home/power_monitor/voltage";
const char* topic_current = "home/power_monitor/current";
const char* topic_power   = "home/power_monitor/power";
const char* topic_energy  = "home/power_monitor/energy";

unsigned long lastReconnectAttempt = 0;
unsigned long lastPublish = 0;

// -------------------- Wi-Fi Setup --------------------
void setup_wifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi connected, IP: " + WiFi.localIP().toString());
}

// -------------------- Save & Load Relay States --------------------
void saveRelayState(int index, bool state) {
  preferences.begin("relayStates", false);
  preferences.putBool(String(index).c_str(), state);
  preferences.end();
}

bool loadRelayState(int index) {
  preferences.begin("relayStates", true);
  bool state = preferences.getBool(String(index).c_str(), false);
  preferences.end();
  return state;
}

// -------------------- MQTT Callback --------------------
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) message += (char)payload[i];
  message.trim();

  for (int i = 0; i < relayCount; i++) {
    if (String(topic) == relays[i].commandTopic) {
      bool newState = message.equalsIgnoreCase("ON");
      digitalWrite(relays[i].pin, newState ? HIGH : LOW);
      relays[i].state = newState;
      client.publish(relays[i].stateTopic, newState ? "ON" : "OFF", true);
      saveRelayState(i, newState);
      Serial.println(String(relays[i].name) + (newState ? " → ON" : " → OFF"));
    }
  }
}

// -------------------- MQTT Reconnect --------------------
boolean reconnect() {
  if (WiFi.status() != WL_CONNECTED) return false;
  Serial.print("Reconnecting to MQTT...");
  if (client.connect("ESP32_8Relay_PZEM", mqtt_user, mqtt_password)) {
    Serial.println("connected ✅");
    for (int i = 0; i < relayCount; i++) {
      client.subscribe(relays[i].commandTopic);
      client.publish(relays[i].stateTopic, relays[i].state ? "ON" : "OFF", true);
    }
    return true;
  } else {
    Serial.print("failed, rc=");
    Serial.println(client.state());
    return false;
  }
}

// -------------------- Setup --------------------
void setup() {
  Serial.begin(115200);
  Serial.println("🔌 Booting ESP32 with PZEM + Relays...");

  setup_wifi();

  for (int i = 0; i < relayCount; i++) {
    pinMode(relays[i].pin, OUTPUT);
    relays[i].state = loadRelayState(i);
    digitalWrite(relays[i].pin, relays[i].state ? HIGH : LOW);
    Serial.println(String(relays[i].name) + " restored: " + (relays[i].state ? "ON" : "OFF"));
  }

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.setKeepAlive(60);
  lastReconnectAttempt = 0;
}

// -------------------- Main Loop --------------------
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    delay(2000);
    return;
  }

  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) lastReconnectAttempt = 0;
    }
  } else {
    client.loop();
  }

  unsigned long now = millis();
  if (now - lastPublish > 5000) {
    lastPublish = now;
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();

    if (isnan(voltage)) {
      Serial.println("⚠️ Failed to read PZEM!");
    } else {
      Serial.printf("V: %.2fV | I: %.3fA | P: %.2fW | E: %.3fkWh\n", voltage, current, power, energy);

      char msg[16];
      dtostrf(voltage, 4, 2, msg);  client.publish(topic_voltage, msg, true);
      dtostrf(current, 4, 3, msg);  client.publish(topic_current, msg, true);
      dtostrf(power,   4, 2, msg);  client.publish(topic_power, msg, true);
      dtostrf(energy,  4, 3, msg);  client.publish(topic_energy, msg, true);
    }
  }
}
