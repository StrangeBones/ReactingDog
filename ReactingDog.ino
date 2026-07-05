/**
 * ReactingDog
 * -----------
 * An Arduino-powered robotic dog that reacts to ambient sound
 * using a MAX4466 microphone amplifier.
 *
 * Loudness levels:
 *   LOUD  (>= 20) — red LED, ears up, buzzer barks
 *   MID   (>=  1) — blue LED, ears half-up
 *   QUIET (<   1) — green LED, ears down, tail wags
 *
 * Pin assignments
 * ---------------
 *   A0  — MAX4466 microphone (OUT)
 *    3  — RGB LED red   (PWM)
 *    5  — RGB LED green (PWM)
 *    6  — RGB LED blue  (PWM)
 *    9  — tail servo signal
 *   10  — passive buzzer
 *   11  — ear servo signal
 */

#include "src/MicSensor.h"
#include "src/RGBLed.h"
#include "src/TailServo.h"
#include "src/EarServo.h"
#include "src/Buzzer.h"

// ── Thresholds ─────────────────────────────────────────────
const int THRESHOLD_LOUD = 20;
const int THRESHOLD_MID  =  1;

// ── Component instances ────────────────────────────────────
MicSensor mic(A0);
RGBLed    led(3, 5, 6);
TailServo tail(9);
EarServo  ear(11);
Buzzer    buzzer(10);

// ──────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  led.begin();
  tail.begin();
  ear.begin();
  buzzer.begin();
}

void loop() {
  int loudness = mic.read();
  Serial.println(loudness);

  if (loudness >= THRESHOLD_LOUD) {
    // ── LOUD: alarmed ──
    led.setColor(255, 0, 0);
    tail.still();
    ear.up();
    buzzer.bark();
    delay(2000);

  } else if (loudness >= THRESHOLD_MID) {
    // ── MID: alert ──
    led.setColor(0, 0, 255);
    tail.still();
    ear.half();
    delay(3000);

  } else {
    // ── QUIET: relaxed ──
    led.setColor(0, 255, 0);
    ear.down();
    tail.wag();
    delay(150);
    analogRead(A0); // flush ADC after servo noise
  }
}
