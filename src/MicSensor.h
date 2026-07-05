#pragma once

#include <Arduino.h>

/**
 * @brief Reads loudness from a MAX4466 electret microphone amplifier.
 *
 * Averages multiple peak-to-peak amplitude measurements over short
 * sampling windows to produce a stable loudness value.
 */
class MicSensor {
public:
  /**
   * @param pin        Analog pin connected to the MAX4466 OUT.
   * @param samples    Number of measurement windows to average (default 5).
   * @param windowMs   Duration of each sampling window in ms (default 20).
   */
  MicSensor(int pin, int samples = 5, unsigned long windowMs = 20);

  /**
   * @brief Perform a full measurement cycle.
   * @return Averaged peak-to-peak amplitude (0–1023).
   */
  int read();

private:
  int           _pin;
  int           _samples;
  unsigned long _windowMs;
};
