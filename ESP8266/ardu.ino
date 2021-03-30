#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include "uMQTTBroker.h"

// MARK: - WIFI
#define WLAN_SSID "UPC2253338"   // Wi-Fi SSID
#define WLAN_PASS "Tefvba3ehtCr" // Wi-Fi Password
WiFiClient client;

// MARK: - MQTT
#define APP_ID "esp"
#define DATASTORE "config"
#define MQTT_PORT 1883

// MARK: - mDNS
MDNSResponder::hMDNSService hMDNSService = 0;

// MARK: - Strip
#include <Adafruit_NeoPixel.h>

class Strip
{
public:
  uint8_t effect;
  uint8_t effects;
  uint16_t effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype)
  {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset()
  {
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime)
  {
    currentTime = 0;
    currentChild = 0;
    childs = totchilds;
    timeBased = timebased;
    cycles = tottime;
  }
};

void strips_loop()
{
  if (strip0_loop0() & 0x01)
    strip_0.strip.show();
}

uint8_t strip0_loop0()
{
  uint8_t ret = 0x00;
  switch (strip0loop0.currentChild)
  {
  }
  if (ret & 0x02)
  {
    ret &= 0xfd;
    if (strip0loop0.currentChild + 1 >= strip0loop0.childs)
    {
      strip0loop0.currentChild = 0;
      if (++strip0loop0.currentTime >= strip0loop0.cycles)
      {
        strip0loop0.currentTime = 0;
        ret |= 0x02;
      }
    }
    else
    {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

Strip strip_0(60, 8, 60, NEO_RGB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);

// MARK: - MQTT Broker delegate methods
class MDLMQTTBroker : public uMQTTBroker
{
public:
  virtual bool onConnect(IPAddress addr, uint16_t client_count)
  {
    Serial.println(addr.toString() + " connected");
    return true;
  }

  virtual void onData(String topic, const char *data, uint32_t length)
  {
    if (data.arguments[0] == 'A')
    {
      strip_0.strip.begin();
      if (strip0_loop0() & 0x01)
      {
        strip_0.strip.show();
      }
    }
  }
};

MDLMQTTBroker broker;

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

  hMDNSService = MDNS.addService(0, "mqtt", "udp", MQTT_PORT);
}

void setup()
{
  Serial.begin(115200);
  setupWiFi();
  setupMQTTBroker();
  setupMDNS();
  strip_0.strip.begin();
}

void loop()
{
  MDNS.update();
  strips_loop();
}
