# 🐶 ReactingDog

An Arduino-powered robotic dog that listens to ambient sound and reacts in real time — wagging its tail when it's quiet, perking up its ears when it hears something, and barking back when things get loud.

---

## Demo behavior

| Loudness | LED | Ears | Tail | Buzzer |
|---|---|---|---|---|
| Quiet (`< 1`) | 🟢 Green | Down | Wagging | — |
| Mid (`≥ 1`) | 🔵 Blue | Half-up | Still | — |
| Loud (`≥ 20`) | 🔴 Red | Up | Still | Bark |

---

## Hardware

| Component | Model | Pin |
|---|---|---|
| Microcontroller | Arduino Uno / Nano | — |
| Microphone amplifier | MAX4466 | A0 |
| RGB LED (common cathode) | — | 3 (R), 5 (G), 6 (B) |
| Tail servo | SG90 or similar | 9 |
| Ear servo | SG90 or similar | 11 |
| Passive buzzer | — | 10 |

> **Power note:** Two servos drawing current simultaneously can cause voltage dips on the Arduino 5 V rail. Consider powering the servos from a separate 5 V supply (shared GND) if you observe resets or erratic behavior.

---

## Wiring diagram

```
MAX4466  OUT ──────────────► A0
         GND ──────────────► GND
         VCC ──────────────► 3.3 V

RGB LED  R   ──[220 Ω]────► D3
         G   ──[220 Ω]────► D5
         B   ──[220 Ω]────► D6
         GND ──────────────► GND

Tail servo   signal ───────► D9
Ear  servo   signal ───────► D11
Both servos  VCC/GND ──────► external 5 V / GND

Passive buzzer (+) ────────► D10
               (-) ────────► GND
```

---

## Project structure

```
ReactingDog/
├── ReactingDog.ino      # Main sketch — setup() & loop()
├── README.md
├── LICENSE
└── src/
    ├── MicSensor.h/.cpp  # MAX4466 loudness measurement
    ├── RGBLed.h/.cpp     # Common-cathode RGB LED
    ├── TailServo.h/.cpp  # Tail wag / still
    ├── EarServo.h/.cpp   # Ear positions (down / half / up)
    └── Buzzer.h/.cpp     # Two-bark "Wuff" sound
```

---

## How to build & upload

1. Open `ReactingDog.ino` in the **Arduino IDE** (≥ 1.8) or **Arduino IDE 2**.
2. Make sure the `Servo` library is available — it ships with the IDE by default.
3. Select your board (**Tools → Board**) and port (**Tools → Port**).
4. Click **Upload** (Ctrl + U).
5. Open **Serial Monitor** at **9600 baud** to watch live loudness values.

---

## Calibration

Adjust the two thresholds in `ReactingDog.ino` to match your environment:

```cpp
const int THRESHOLD_LOUD = 20;  // peak-to-peak amplitude for "loud"
const int THRESHOLD_MID  =  1;  // peak-to-peak amplitude for "mid"
```

The `MicSensor` constructor also accepts custom sample count and window length:

```cpp
// 8 windows × 30 ms each for a smoother reading in noisy environments
MicSensor mic(A0, 8, 30);
```

---

## License

MIT — see [`LICENSE`](LICENSE).
