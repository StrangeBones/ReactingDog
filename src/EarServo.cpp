#include "EarServo.h"

EarServo::EarServo(int pin) : _pin(pin) {}

void EarServo::begin() {
  _servo.attach(_pin);
  down();
}

void EarServo::down() { _servo.write(30);  }
void EarServo::half() { _servo.write(75);  }
void EarServo::up()   { _servo.write(160); }
