#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Configurare pinii pentru CE și CSN
#define CE_PIN 9
#define CSN_PIN 10

// Creează un obiect RF24
RF24 radio(CE_PIN, CSN_PIN);

// Adresele de comunicare
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); // Setează puterea de transmisie la maxim
  radio.setDataRate(RF24_250KBPS); // Setează viteza de transmisie la minim (250 kbps)
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    uint16_t receivedData;
    radio.read(&receivedData, sizeof(receivedData));


    Serial.println(receivedData, BIN);
  }
}
