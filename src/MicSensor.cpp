#include "MicSensor.h"

MicSensor::MicSensor(int pin, int samples, unsigned long windowMs)
  : _pin(pin), _samples(samples), _windowMs(windowMs) {}

int MicSensor::read() {
  long total = 0;

  for (int i = 0; i < _samples; i++) {
    int signalMax = 0;
    int signalMin = 1023;

    unsigned long start = millis();
    while (millis() - start < _windowMs) {
      int sample = analogRead(_pin);
      if (sample > signalMax) signalMax = sample;
      if (sample < signalMin) signalMin = sample;
    }

    total += (signalMax - signalMin);
  }

  return (int)(total / _samples);
}
