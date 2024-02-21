#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define bt1 1
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

void setup() {
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
  stateBtn = stateBtn & !digitalRead(bt0);
}