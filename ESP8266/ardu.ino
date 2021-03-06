#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include "uMQTTBroker.h"
#include "MessageMapper.h"

// MARK: - WIFI
#include "config.h"
WiFiClient client;

// MARK: - mDNS
MDNSResponder::hMDNSService hMDNSService = 0;

// MARK: - MQTT
#define APP_ID "esp"
#define DATASTORE "config"
#define MQTT_PORT 1883

// MARK: - LIGHT CONTROLLER
#include "Rainbow.h"
#include "NeopixelLightController.h"
#include "RainbowAnimationAdapter.h"
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define LEDNUMBER 60

Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(LEDNUMBER, PIN, NEO_GRB + NEO_KHZ800);
NeopixelLightController controller = NeopixelLightController(neoPixel);
Rainbow rainbow = Rainbow(controller, LEDNUMBER);
RainbowAnimationAdapter adapter = RainbowAnimationAdapter(&rainbow);

// MARK: - MQTT Broker delegate methods
class MLMQTTBroker : public uMQTTBroker
{
public:
  bool onConnect(IPAddress addr, uint16_t client_count)
  {
    Serial.println(addr.toString() + " connected");
    return true;
  }

  void onData(String topic, const char *data, uint32_t length)
  {
    Serial.println(topic + ": " + (String)data);
    MessageMapper::mapToRainbow(data, &adapter);
  }
};

MLMQTTBroker broker;

void setupWiFi()
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to " + (String)WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void setupMQTTBroker()
{
  broker.init();

  broker.subscribe(APP_ID "/" DATASTORE);
  Serial.println("MQTT broker started");
}

void setupMDNS()
{
  if (!MDNS.begin(String("esp8266-" + String(ESP.getChipId())), WiFi.localIP()))
  {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  hMDNSService = MDNS.addService(0, "mqtt", "tcp", MQTT_PORT);
}

void setup()
{
  Serial.begin(115200);
  setupWiFi();
  setupMQTTBroker();
  setupMDNS();
}

void loop()
{
  MDNS.update();
  adapter.updateAnimations(millis());
}
