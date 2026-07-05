#include "TailServo.h"

TailServo::TailServo(int pin) : _pin(pin) {}

void TailServo::begin() {
  _servo.attach(_pin);
  still();
}

void TailServo::still() {
  _servo.write(90);
}

void TailServo::wag() {
  _servo.write(60);
  delay(150);
  _servo.write(120);
  delay(150);
  _servo.write(90);
}
