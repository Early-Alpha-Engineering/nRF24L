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

bool debug = true;
bool up_button_state = 0;
bool down_button_state = 0;
bool left_button_state = 0;
bool right_button_state = 0;
bool start_button_state = 0;
bool select_button_state = 0;
bool analog_button_state = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);    // Setează puterea de transmisie la maxim
  radio.setDataRate(RF24_250KBPS);  // Setează viteza de transmisie la minim (250 kbps)
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    uint16_t receivedData;
    radio.read(&receivedData, sizeof(receivedData));

    // Extract the first 2 bits (2345)
    uint8_t x = (receivedData >> 11) & 0x0F;
    // // Extract the next 4 bits (6789)
    uint8_t y = (receivedData >> 7) & 0x0F;

    up_button_state = (receivedData >> 3) & 0x01;
    down_button_state = (receivedData >> 1) & 0x01;
    left_button_state = (receivedData >> 0) & 0x01;
    right_button_state = (receivedData >> 2) & 0x01;
    start_button_state = (receivedData >> 4) & 0x01;
    select_button_state = (receivedData >> 5) & 0x01;
    analog_button_state = (receivedData >> 6) & 0x01;

    if (debug) {
      // Print the extracted values for debugging
      Serial.print("x: ");
      Serial.print(x);
      Serial.print(" y: ");
      Serial.print(y);

      Serial.print(" analog_button: ");
      Serial.print(analog_button_state);

      Serial.print(" select_button: ");
      Serial.print(select_button_state);

      Serial.print(" start_button: ");
      Serial.print(start_button_state);

      Serial.print(" up_button: ");
      Serial.print(up_button_state);

      Serial.print(" right_button: ");
      Serial.print(right_button_state);

      Serial.print(" down_button: ");
      Serial.print(down_button_state);

      Serial.print(" left_button: ");
      Serial.println(left_button_state);
    }
  }
}