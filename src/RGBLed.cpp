#include "RGBLed.h"

RGBLed::RGBLed(int redPin, int greenPin, int bluePin)
  : _r(redPin), _g(greenPin), _b(bluePin) {}

void RGBLed::begin() {
  pinMode(_r, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_b, OUTPUT);
}

void RGBLed::setColor(int r, int g, int b) {
  analogWrite(_r, r);
  analogWrite(_g, g);
  analogWrite(_b, b);
}

void RGBLed::off() {
  setColor(0, 0, 0);
}
