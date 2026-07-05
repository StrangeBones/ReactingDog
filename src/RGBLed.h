#pragma once

#include <Arduino.h>

/**
 * @brief Controls a common-cathode RGB LED via PWM pins.
 */
class RGBLed {
public:
  /**
   * @param redPin   PWM pin for the red channel.
   * @param greenPin PWM pin for the green channel.
   * @param bluePin  PWM pin for the blue channel.
   */
  RGBLed(int redPin, int greenPin, int bluePin);

  void begin();

  /** @brief Set LED color with 0–255 values per channel. */
  void setColor(int r, int g, int b);

  void off();

private:
  int _r, _g, _b;
};
