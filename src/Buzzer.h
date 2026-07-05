#pragma once

#include <Arduino.h>

/**
 * @brief Drives a passive buzzer to produce a two-bark "Wuff" sound.
 */
class Buzzer {
public:
  explicit Buzzer(int pin);

  void begin();

  /**
   * @brief Play a two-bark sequence (deep wuff → mid bark → high peak).
   * Blocking — takes ~1 s total.
   */
  void bark();

private:
  int _pin;
};
