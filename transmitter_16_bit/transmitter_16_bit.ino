#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";
const bool debug = false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  uint16_t dataToSend = 0b1000000000000000;

  bool success = radio.write(&dataToSend, sizeof(dataToSend));
}
