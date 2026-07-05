/**
 * Traffy
 * 
 * An Arduino-powered robotic dog that reacts to ambient sound
 * using a MAX4466 microphone amplifier.
 *
 * Loudness levels:
 *   LOUD  (>= 7) — red LED, ears up, buzzer barks
 *   MID   (>=  4) — blue LED, ears half-up
 *   QUIET (<   1) — green LED, ears down, tail wags
 *
 * Pin assignments
 *   A0  - MAX4466 microphone
 *    3  - RGB LED red   (PWM)
 *    5  - RGB LED green (PWM)
 *    6  - RGB LED blue  (PWM)
 *    9  - tail servo signal
 *   10  - passive buzzer
 *   11  - ear servo signal
 */

#include <Servo.h>

//microphone (MAX4466)
const int micPin = A0;

//LEDs
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

//servo motor (tail)
const int servoPin = 9;
Servo tailServo;

//servo motor (ears)
const int earServoPin = 11;
Servo earServo;

//passive buzzer
const int buzzerPin = 10;

//thresholds
const int blueThreshold = 1;
const int redThreshold = 20;

//setup
void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  //tail servo 
  tailServo.attach(servoPin);
  tailServo.write(90);

  //ear servo 
  earServo.attach(earServoPin);
  earServo.write(30); // Ohren unten
}

void loop() {

  int loudness = 0;

  // 5 Messungen mitteln
  for (int i = 0; i < 5; i++) {

    int signalMax = 0;
    int signalMin = 1023;

    unsigned long start = millis();

    while (millis() - start < 20) {
      int sample = analogRead(micPin);

      if (sample > signalMax)
        signalMax = sample;

      if (sample < signalMin)
        signalMin = sample;
    }

    loudness += (signalMax - signalMin);
  }

  loudness /= 5;

  Serial.println(loudness);

  //loud input
  if (loudness >= redThreshold) {

    setColor(255, 0, 0);

    tailServo.write(90);     // Schwanz still
    earServo.write(160);     // Ohren oben

    barkSound();

    delay(2000);
  }

  //mid input
  else if (loudness >= blueThreshold) {

    setColor(0, 0, 255);

    tailServo.write(90);
    earServo.write(75);      // Ohren halb oben

    delay(3000);
  }

  //quiet input
  else {

    setColor(0, 255, 0);

    earServo.write(30);      // Ohren unten

    wagTail();

    delay(150);
    analogRead(micPin);
  }
}

//RPG-LED function 
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

//tail
void wagTail() {

  tailServo.write(60);
  delay(150);

  tailServo.write(120);
  delay(150);

  tailServo.write(90);
}

//buzzer 
void barkSound() {

  for (int i = 0; i < 2; i++) {

    // Tiefes "Wuff"
    tone(buzzerPin, 200);
    delay(80);

    // Mittleres Bellen
    tone(buzzerPin, 600);
    delay(120);

    // Hoher Peak
    tone(buzzerPin, 900);
    delay(100);

    noTone(buzzerPin);
    delay(60);
  }

  delay(200);
}
