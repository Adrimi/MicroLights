#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include "uMQTTBroker.h"
#include "Strip.h"

// MARK: - WIFI 
#define WLAN_SSID       "UPC2253338"  // Wi-Fi SSID
#define WLAN_PASS       "Tefvba3ehtCr"  // Wi-Fi Password
WiFiClient client;

// MARK: - MQTT 
#define APP_ID      "esp" 
#define DATASTORE   "config" 
#define MQTT_PORT   1883

// MARK: - mDNS
MDNSResponder::hMDNSService hMDNSService = 0;

// MARK: - Strip
Strip strip_0(60, 8, 60, NEO_RGB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);

class MDLMQTTBroker: public uMQTTBroker {
  public:
  virtual bool onConnect(IPAddress addr, uint16_t client_count) {
    Serial.println(addr.toString()+" connected");
    return true;
  }

  virtual void onData(String topic, const char *data, uint32_t length) {
    String config; 
    sscanf(data, "%d", config);
    
    if (config == "start") {
      strip_0.strip.begin();
      if(strip0_loop0() & 0x01) {
        strip_0.strip.show();
      }
    } 

    if (sscanf(data, "%d,%d,%d,%d,%d.", &red, &green, &blue, &dimmer, &address) == 5) {
      dmx.write(address, dimmer);
      dmx.write(address+1, blue);
      dmx.write(address+2, green);
      dmx.write(address+3, red);

      dmx.update();
    } 
  }
};

MDLMQTTBroker broker;

void setupWiFi() {
  Serial.println(); Serial.println();
  Serial.print("Connecting to "+(String)WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void setupMQTTBroker() {
  broker.init();

  broker.subscribe(APP_ID "/" DATASTORE);
  Serial.println("MQTT broker started");
}

void setupMDNS() {
  if (!MDNS.begin(String("esp8266-" + String(ESP.getChipId())), WiFi.localIP())) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  hMDNSService = MDNS.addService(0, "mqtt", "udp", MQTT_PORT);
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupMQTTBroker();
  setupMDNS();
}

void loop() {
  MDNS.update();
}
