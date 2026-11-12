# 01: Parts and Theory

This page explains what each part does and the ideas behind the project. If you already know how a potentiometer and a buzzer work, skip ahead to [`02-coding-basics.md`](02-coding-basics.md).

## The big idea

So far in OPS, every input has been **digital**: a button is either pressed or not. This project adds an **analog** input, a knob that can be anywhere in a range. The Arduino reads where the knob is, turns that into a frequency, and plays that frequency through a buzzer. The button decides *when* the sound plays.

```
 Knob position  →  analogRead()  →  map()  →  tone()  →  Buzzer
  (0 V – 5 V)       (0 – 1023)      (Hz)
```

## Digital vs. analog

| | Digital | Analog |
|---|---|---|
| Possible values | Only two: `HIGH` or `LOW` | A range of values |
| Example | Button, switch | Potentiometer, light sensor, temperature sensor |
| Arduino function | `digitalRead()` | `analogRead()` |
| Nano pins | D0–D13 (and A0–A7 can also work as digital, except A6/A7) | A0–A7 |

### How the Arduino reads an analog voltage

The Nano has an **analog-to-digital converter (ADC)**. It measures the voltage on an analog pin and turns it into a whole number:

- 0 V → `0`
- 5 V → `1023`
- Anything in between scales evenly. 2.5 V reads as about `512`.

Why 1023? The Nano's ADC is **10-bit**, so it has 2¹⁰ = 1024 possible values (0 through 1023).

## Parts

### Arduino Nano

The same board from earlier OPS projects. This time we use one of its analog pins (**A0**) for the first time.

### Potentiometer

A potentiometer (or "pot") is a resistor with a third pin that slides along it when you turn the knob.

```
   5V ──[ left ]───────┐
                       │  resistive track
          wiper ──▶ ( middle ) ──▶ A0
                       │
  GND ──[ right ]──────┘
```

- The two **outer legs** connect to 5 V and GND. Together they make a fixed path across the full resistance (10 kΩ).
- The **middle leg (wiper)** touches the track wherever the knob is pointing.

This is called a **voltage divider**. With the knob all the way to one side, the wiper sits at 0 V. All the way to the other side, it sits at 5 V. In the middle, about 2.5 V.

> Swapping the two outer legs just reverses the direction. Turning clockwise will lower the pitch instead of raising it. Neither way is wrong.

### Buzzer

A piezo buzzer has a thin disc that bends when voltage is applied. Switch the voltage on and off fast enough and the disc vibrates, which pushes air and makes sound.

- The **speed** of switching is the **frequency**, measured in hertz (Hz, vibrations per second).
- Higher frequency = higher pitch.

| Frequency | Sounds like |
|---|---|
| ~100 Hz | Low hum |
| 262 Hz | Middle C on a piano |
| 440 Hz | The A that orchestras tune to |
| ~2000 Hz | High, sharp beep |

**Passive vs. active buzzers:** a passive buzzer only makes sound when *you* switch it on and off, so you control the pitch. An active buzzer has a circuit inside that makes its own fixed tone the moment it gets power. For this project you need a **passive** one. If you're not sure which you have, see [troubleshooting](troubleshooting.md#the-buzzer-only-makes-one-pitch).

Most buzzers have a longer leg or a `+` mark. That side goes to the Arduino pin.

### Pushbutton

Same as OPS 4. We use the Nano's built-in **pull-up resistor** (`INPUT_PULLUP`):

- Released → pin reads `HIGH`
- Pressed → pin connects to GND and reads `LOW`

That's backwards from what you might expect, so remember: **`LOW` means pressed.**

## How it all fits together

1. The pot sets a voltage on A0 (0–5 V).
2. `analogRead(A0)` gives a number from 0–1023.
3. `map()` scales that into a frequency range, for example 100–2000 Hz.
4. If the button is pressed, `tone()` plays that frequency on the buzzer.
5. If the button is released, `noTone()` stops the sound.
6. `loop()` repeats this many times per second, so turning the knob changes the pitch right away.

Next: [`02-coding-basics.md`](02-coding-basics.md)
