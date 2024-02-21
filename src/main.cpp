#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define bt1 A0
#define bt2 2
#define bt3 3
#define bt4 4
#define bt5 5
#define bt6 6
#define bt7 7
#define bt8 8

#define CE 9
#define CSN 10

const byte slaveAddress[5] = {'S','s','T','M','U'};

uint8_t stateBtn = 0x0;
uint32_t message = 0x0;

void ButtonReading();
void MapButton();

RF24 radio(CE, CSN);

void setup() {
  Serial.begin(9600);

  // setup radio
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(3,5); // delay, count
  radio.printDetails();
  radio.openWritingPipe(slaveAddress);
  
  // put your setup code here, to run once:
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  pinMode(bt5, INPUT_PULLUP);
  pinMode(bt6, INPUT_PULLUP);
  pinMode(bt7, INPUT_PULLUP);
  pinMode(bt8, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // populate button
  ButtonReading();

  // mapping state button to message
  MapButton();

  // serial print
  Serial.println(message, HEX);
}

void ResetButton(){
  stateBtn = 0x0;
}

void ButtonReading(){
  // Reset Button
  ResetButton();

  // read button state
  stateBtn |= (!digitalRead(bt1) << 0);
  stateBtn |= (!digitalRead(bt2) << 1);
  stateBtn |= (!digitalRead(bt3) << 2);
  stateBtn |= (!digitalRead(bt4) << 3);
  stateBtn |= (!digitalRead(bt5) << 4);
  stateBtn |= (!digitalRead(bt6) << 5);
  stateBtn |= (!digitalRead(bt7) << 6);
  stateBtn |= (!digitalRead(bt8) << 7);
}

void MapButton(){
  message = 0x0;

  if (stateBtn == 1) {
    message = 0xF30CFF00;
  }

  if (stateBtn == 2) {
    message = 0xE718FF00;
  }

  if (stateBtn == 4) {
    message = 0xA15EFF00;
  }

  if (stateBtn == 8) {
    message = 0xF708FF00;
  }

  if (stateBtn == 16) {
    message = 0xE31CFF00;
  }

  if (stateBtn == 32) {
    message = 0xA55AFF00;
  }

  if (stateBtn == 64) {
    message = 0xAD52FF00;
  }

  if (stateBtn == 128) {
    message = 0xBD42FF00;
  }
}