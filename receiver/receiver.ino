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
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  for (int i = 30; i < 46; i++) {
    pinMode(i, OUTPUT);
  }
  myservo.attach(9);
}

void loop() {
  if (radio.available()) {
      int value[17];
      radio.read(&value, sizeof(value));
      Serial.println("READ");
      for (int i = 0; i <= 16; i++) {
        Serial.print(value[i]);
      }
      for (int i = 1; i <= 16; i++) {
        if(value[i] == 1) {
          digitalWrite(pins[i-1], LOW); 
        } else if(value[i] == 0) {
          digitalWrite(pins[i-1], HIGH);
        }
      }
      // which index to servo?
      myservo.write(value[0]);
      
  } else {
    for (int i = 1; i <= 16; i++) {
      digitalWrite(pins[i-1], LOW);
    }
  }
}
