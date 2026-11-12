# OPS 5: Pitch Controller

TXST IEEE Student Branch, OPS Project #5.

Fifth project in the OPS series. This project uses an Arduino, a potentiometer, a piezo buzzer, and a pushbutton to build a simple handheld instrument. Turn the knob to pick a pitch and press the button to play it. You will learn how to read analog inputs, scale values with `map()`, and generate sound with `tone()`.

Board: **Arduino Nano**. Pin numbers, diagrams, and code here are written for it.

Coming from [OPS4](https://github.com/IEEE-TXST/OPS_4)? You already know digital outputs, timing, and reading a pull-up button. This project adds analog input, turning a range of voltages into a number the Arduino can use, and outputting sound instead of light.

## Session Goals

By the end of today, students will:

- Understand the difference between digital and analog inputs
- Learn how a potentiometer works as a voltage divider
- Use `analogRead()` and `map()` to convert a sensor reading into a useful range
- Use `tone()` and `noTone()` to drive a piezo buzzer at different frequencies
- Build a working pitch controller that plays a note only while the button is held

## Where to look

| I want to... | Go here |
|---|---|
| Understand the parts and the analog/sound theory | [`01-parts-and-theory.md`](01-parts-and-theory.md) |
| Understand the Arduino code (`analogRead`, `map`, `tone`) | [`02-coding-basics.md`](02-coding-basics.md) |
| Actually wire it up and write the program | [`03-build-the-circuit.md`](03-build-the-circuit.md) |
| Try the harder version or add enhancements | [`04-going-further.md`](04-going-further.md) |
| Fix something that isn't working | [`troubleshooting.md`](troubleshooting.md) |

You do not have to read all of this front to back. If you are comfortable with the basics already, jump straight to [building](03-build-the-circuit.md).

## Parts list

- 1 Arduino Nano
- 1 breadboard
- 1 potentiometer (10 kΩ recommended)
- 1 passive piezo buzzer
- 1 pushbutton
- Jumper wires
- USB cable
- Optional: 100 Ω resistor in series with the buzzer (makes it quieter), an LED + 220 Ω resistor as a "note playing" indicator, or a second button for extra features

> **Note:** Use a **passive** buzzer. An active buzzer has its own built-in tone and will only beep at one pitch no matter what the code does. See [Passive vs. active buzzers](Docs/01-parts-and-theory.md#passive-piezo-buzzer) and [how to tell which one you have](Docs/troubleshooting.md#the-buzzer-only-makes-one-pitch).

## Code

- [`starter_code/OPS5_pitch_controller_starter/`](starter_code/OPS5_pitch_controller_starter/): open this first. It has `TODO`s instead of finished code, and [Step 6 of the build guide](Docs/03-build-the-circuit.md#step-6-write-the-program) walks you through them.
- [`solution_code/OPS5_pitch_controller_solution/`](solution_code/OPS5_pitch_controller_solution/): the finished version, for when you're stuck or want to compare your code.

Both are Arduino IDE sketch folders, so open the folder itself, not just the `.ino` inside.

## Wiring, at a glance

| Part | Pin |
|---|---|
| Potentiometer left leg | 5V |
| Potentiometer middle leg (wiper) | A0 |
| Potentiometer right leg | GND |
| Buzzer + | D8 |
| Buzzer − | GND |
| Pushbutton (one side) | D2 |
| Pushbutton (other side) | GND |
| Optional indicator LED | D13 (through 220 Ω to GND) |

Full step-by-step wiring, with a test after each part, is in [`Docs/03-build-the-circuit.md`](Docs/03-build-the-circuit.md#wiring-table).

The button uses the Nano's internal pull-up (`INPUT_PULLUP`), so it reads `HIGH` when released and `LOW` when pressed. No external resistor is needed. ([More on the button](Docs/01-parts-and-theory.md#pushbutton))

A potentiometer is a [voltage divider](Docs/01-parts-and-theory.md#potentiometer). Turning the knob moves the middle pin between 0 V and 5 V, and [`analogRead()`](Docs/02-coding-basics.md#analogread) turns that into a number from 0 to 1023. The program uses [`map()`](Docs/02-coding-basics.md#map) to scale that number into a frequency range the buzzer can play (for example, 100 Hz to 2000 Hz), then passes it to [`tone()`](Docs/02-coding-basics.md#tone-and-notone).

## Expected behavior

- **Button released:** the buzzer is silent.
- **Button held:** the buzzer plays a steady tone.
- **Turning the knob while holding the button:** the pitch slides up and down smoothly. One direction is low, the other is high.
- **Releasing the button:** the sound stops right away.

Open the [Serial Monitor](Docs/02-coding-basics.md#serial-monitor-for-debugging) (9600 baud) to watch the raw potentiometer reading and the frequency being played update in real time. Use the [build checklist](Docs/03-build-the-circuit.md#checklist) to confirm everything works.

Not behaving like this? Check [`Docs/troubleshooting.md`](Docs/troubleshooting.md).

## Going further

Once the basic version works, try:

- [Snapping the knob to real musical notes](Docs/04-going-further.md#challenge-2-snap-to-real-musical-notes) (C, D, E, ...) instead of a smooth slide
- [Adding a second button that switches between octaves](Docs/04-going-further.md#challenge-3-octave-button)
- [Lighting an LED whose brightness follows the pitch](Docs/04-going-further.md#challenge-4-led-that-follows-the-pitch)
- [Making a short melody play when the button is double-pressed](Docs/04-going-further.md#challenge-5-play-a-melody)
- [Bringing back the OPS 4 state machine](Docs/04-going-further.md#challenge-6-bring-back-the-state-machine) to switch between modes

See [`Docs/04-going-further.md`](Docs/04-going-further.md) for hints.
