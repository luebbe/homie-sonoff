#define FW_NAME "sonoff-dht22"
#define FW_VERSION "1.0.7"

#include <Homie.hpp>
#include "ButtonNode.hpp"
#include "DHT22Node.hpp"
#include "RelayNode.hpp"
#include "SPI.h"  // Compilation fails if SPI.h is not included even though BME280Node, which needs SPI.h is not part of the project
#include "Wire.h" // Same

const int PIN_BUTTON = 0;
const int PIN_RELAY = 12;
const int PIN_LED = 13;
const int PIN_DHT = 14;

RelayNode relayNode("relay", "relay", PIN_RELAY, PIN_LED);
DHT22Node dht22Node("dht22", "dht22", PIN_DHT);

// Initialize button node with callback to button press
ButtonNode buttonNode("button", "button", PIN_BUTTON, []() {
  relayNode.toggleRelay();
});

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial << endl
         << endl;

  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Homie_setFirmware(FW_NAME, FW_VERSION);

  Homie.disableResetTrigger();
  Homie.setup();
}

void loop()
{
  Homie.loop();
}
