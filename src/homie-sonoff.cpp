#define FW_NAME "sonoff"
#define FW_VERSION "1.0.4"

#include <Homie.h>
#include "ota.hpp"
#include "welcome.hpp"
#include "homie-node-collection.hpp"

// I prefer to see the first ESP Boot messages as well, hence 74880 instead of 115200
#define SERIAL_SPEED 74880

const int PIN_BUTTON = 0;
const int PIN_RELAY = 12;
const int PIN_LED = 13;
const int PIN_DHT = 14;

// Setup OTA logging via Homie logger
OtaLogger ota;
Welcome welcome(FW_NAME, FW_VERSION);

RelayNode relayNode("relay", PIN_RELAY, PIN_LED);
DHT22Node dht22Node("dht22", PIN_DHT);

// Initialize button node with callback to button press
ButtonNode buttonNode("button", PIN_BUTTON, []() {
  relayNode.toggleRelay();
});

void setupHandler() {
  // This is called after the MQTT_CONNECTED event
  ota.setup();
}

void loopHandler() {
  ota.loop();
}

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial << endl << endl;

  welcome.show();
  ota.setup();

  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Homie_setFirmware(FW_NAME, FW_VERSION);

  Homie.disableResetTrigger();
  Homie.disableLedFeedback();

  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
