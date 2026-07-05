#pragma once

#include <Servo.h>

/**
 * @brief Controls the dog's tail servo — idle or wagging.
 */
class TailServo {
public:
  /**
   * @param pin  Digital pin connected to the servo signal wire.
   */
  explicit TailServo(int pin);

  void begin();

  /** @brief Hold tail in neutral (90°). */
  void still();

  /**
   * @brief Execute one wag cycle (left → right → center).
   * Blocking — takes ~300 ms.
   */
  void wag();

private:
  int   _pin;
  Servo _servo;
};
