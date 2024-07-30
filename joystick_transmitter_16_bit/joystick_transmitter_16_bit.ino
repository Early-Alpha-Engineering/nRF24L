#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

int up_button     = 2;
int down_button   = 4;
int left_button   = 5;
int right_button  = 3;
int start_button  = 6;
int select_button = 7;
int analog_button = 8;
int x_axis = A0;
int y_axis = A1;

int buttons[] = {left_button, down_button, right_button, up_button, start_button, select_button, analog_button};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  
  // Initialize buttons as input
  for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  // Set the first bit to 1 and reset other bits
  uint16_t finalData = 0b1000000000000000; // First bit set to 1

  // Read button states
  for (int i = 0; i < 7; i++) {
    finalData |= (!digitalRead(buttons[i]) << i); // Set the button state in the correct bit
  }

  // Read analog values
  uint8_t xValue = map(analogRead(x_axis), 0, 1023, 0, 15);  // Map to 4-bit value
  uint8_t yValue = map(analogRead(y_axis), 0, 1023, 0, 15);  // Map to 4-bit value

  xValue &= 0x0F;  // Keep only the lower 4 bits
  yValue &= 0x0F;  // Keep only the lower 4 bits

  // Combine x and y values into finalData
  finalData |= (xValue << 11); // Place xValue in bits 12-15
  finalData |= (yValue << 7);  // Place yValue in bits 8-11

  // Send data
  bool success = radio.write(&finalData, sizeof(finalData));

  // // For debugging
  // Serial.print("X value: ");
  // Serial.print(xValue, BIN);
  // Serial.print(", Y value: ");
  // Serial.print(yValue, BIN);
  // Serial.print(", Buttons Data: ");
  // Serial.print(finalData & 0x7F, BIN); // Only the last 7 bits for button states
  // Serial.print(", Final Data: ");
  // Serial.println(finalData, BIN);
  
  // if (success) {
  //   Serial.println("Data sent successfully");
  // } else {
  //   Serial.println("Data send failed");
  // }
}
