// SimpleTx - the master or the transmitter

#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

#define CE_PIN    9
#define CSN_PIN  10

const byte slaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN); //create radio

char dataToSend[10] = "Message 0";
char txNum = '0';

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SimpleTx Starting");

  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(3,5); // delay, count
  radio.printDetails();
  radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis) {
    send();
    prevMillis = millis();
  }
}

//====================

void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        Serial.println("  Acknowledge received");
        updateMessage();
    }
    else {
        Serial.println("  Tx failed");
    }
}

//================

void updateMessage() {
        // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }
    dataToSend[8] = txNum;
}
