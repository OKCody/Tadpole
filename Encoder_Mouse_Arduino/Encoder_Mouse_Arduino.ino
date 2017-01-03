#include <Mouse.h>

// Red - 5V
// Black - GND
const int encoder_a = 2; // Green - pin 2 - Digital
const int encoder_b = 3; // White - pin 3 - Digital
volatile long encoder = 0;

int initialEncoder = 0;
int finalEncoder = 0;
int delta = 0;

void setup() {
Serial.begin(9600);
pinMode(encoder_a, INPUT_PULLUP);
pinMode(encoder_b, INPUT_PULLUP);

attachInterrupt(0, encoderPinChangeA, CHANGE);
attachInterrupt(1, encoderPinChangeB, CHANGE);
}

void loop() {
  initialEncoder = encoder;
  delayMicroseconds(1);
  finalEncoder = encoder;
  delta = finalEncoder - initialEncoder;
  if(delta != 0){
    Serial.println(delta);
    if(digitalRead(9)){
      Mouse.move(0,0, delta);
    }
  }
}

void encoderPinChangeA() {
  encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? 1 : -1;
  //if(encoder < 0) encoder = 2400;
  //Serial.println(encoder);
  //encoder = 2;
}

void encoderPinChangeB() {
  encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? 1 : -1;
  //if(encoder > 2400) encoder = 0;
  //Serial.println(encoder);
  //encoder = 5;
}
