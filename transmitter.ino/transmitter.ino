#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo myservo;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int pins[16] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  for (int i = 30; i < 46; i++) {
    pinMode(i, INPUT);
  }
  myservo.attach(9);
}

void loop() {
  int frame[17];
  for (int i = 30; i < 46; i++) {
    if(digitalRead(i) == HIGH) {
      frame[i-30] = 1;

    } else if(digitalRead(i) == LOW){
      frame[i-30] = 0;

    }    
  }

  for (int i = 0; i < 16; i++) {
    Serial.print(frame[i]);
  }
  Serial.println("...");
  radio.write(&frame, sizeof(frame));

}
