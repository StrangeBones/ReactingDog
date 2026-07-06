# Traffy

An ELEGOO-powered robotic dog that listens to ambient sound and reacts in real time. Wagging its tail when it's quiet, perking up its ears when it hears something, and barking back when things get loud.

---

## Demo behavior

| Loudness | LED | Ears | Tail | Buzzer |
|---|---|---|---|---|
| Quiet (`< 4`) | Green | Down | Wagging | — |
| Mid (`≥ 4`) | Blue | Half-up | Still | — |
| Loud (`≥ 7`) | Red | Up | Still | Bark |

---

## Hardware

| Component | Model | Pin |
|---|---|---|
| Microcontroller | ELEGOO UNO R3 | — |
| Microphone amplifier | MAX4466 | A0 |
| RGB LED (common cathode) | — | 3 (R), 5 (G), 6 (B) |
| Tail servo | SG90 | 9 |
| Ear servo | SG90 | 11 |
| Passive buzzer | — | 10 |


---

## Wiring diagram

```
MAX4466  OUT ──────────────► A0
         GND ──────────────► GND
         VCC ──────────────► 5 V

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

## How to build & upload

1. Open `TraffyMain.ino` in the **Arduino IDE** (≥ 1.8) or **Arduino IDE 2**.
2. Make sure the `Servo` library is available - it ships with the IDE by default.
3. Select your board (**Tools → Board**) and port (**Tools → Port**).
4. Click **Upload** (Ctrl + U).
5. Open **Serial Monitor** at **9600 baud** to watch live loudness values.

---

## Calibration

Adjust the threshold to match your environment:

```cpp
const int blueThreshold = 4; → mid input
const int redThreshold = 7; → loud input
```
---

## License

MIT — see [`LICENSE`](LICENSE).
