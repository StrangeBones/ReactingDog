#pragma once

#include <Servo.h>

/**
 * @brief Controls the dog's ear servo with three named positions.
 */
class EarServo {
public:
  explicit EarServo(int pin);

  void begin();

  void down();   ///< Ears down  (30°)  — relaxed / quiet
  void half();   ///< Ears half  (75°)  — alert / mid noise
  void up();     ///< Ears up   (160°)  — alarmed / loud noise

private:
  int   _pin;
  Servo _servo;
};
