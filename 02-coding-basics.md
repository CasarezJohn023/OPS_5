# 02: Coding Basics

This page covers the new Arduino functions used in OPS 5. You'll use all of them in the starter code.

## Sketch layout

Every Arduino sketch has the same two parts you already know:

```cpp
void setup() {
  // runs once when the board powers on or resets
}

void loop() {
  // runs over and over, forever
}
```

In this project, `setup()` configures the pins and Serial. `loop()` reads the knob and button, then decides whether to play a sound.

## Naming your pins

Give each pin a name at the top of the file so the rest of the code is easier to read:

```cpp
const int POT_PIN    = A0;
const int BUZZER_PIN = 8;
const int BUTTON_PIN = 2;
```

`const` means the value can't change while the program runs. If you rewire something later, you only have to change one line.

## `pinMode()` for this project

```cpp
pinMode(BUZZER_PIN, OUTPUT);
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

You **don't** need `pinMode()` for the analog pin. `analogRead()` sets it up for you.

## `analogRead()`

```cpp
int potValue = analogRead(POT_PIN);   // 0 to 1023
```

Reads the voltage on an analog pin and returns a whole number from 0 (0 V) to 1023 (5 V).

## `map()`

`map()` converts a number from one range to another.

```cpp
map(value, fromLow, fromHigh, toLow, toHigh)
```

Example:

```cpp
int frequency = map(potValue, 0, 1023, 100, 2000);
```

| `potValue` | `frequency` |
|---|---|
| 0 | 100 |
| 512 | ~1050 |
| 1023 | 2000 |

Things to know:

- `map()` only works with whole numbers. Any decimals get dropped.
- It doesn't clamp. If the input goes outside `fromLow`–`fromHigh`, the output goes outside `toLow`–`toHigh` too. Use `constrain()` if you need a hard limit.
- You can flip the direction by swapping the output values: `map(potValue, 0, 1023, 2000, 100)`.

## `tone()` and `noTone()`

```cpp
tone(BUZZER_PIN, frequency);   // start playing, keeps going until told to stop
noTone(BUZZER_PIN);            // stop playing
```

You can also give a duration in milliseconds:

```cpp
tone(BUZZER_PIN, 440, 500);    // play A for half a second, then stop on its own
```

Things to know:

- `tone()` runs in the background. Your code keeps going while the note plays.
- Calling `tone()` again with a new frequency changes the pitch right away. That's how the knob can slide the pitch smoothly.
- Only one `tone()` can play at a time on the Nano.
- The lowest frequency `tone()` supports is 31 Hz.
- `tone()` uses one of the Nano's internal timers, so `analogWrite()` (PWM) **won't work on pins D3 and D11** while a tone is playing. That matters if you add a dimmable LED later.

## Reading the button

```cpp
if (digitalRead(BUTTON_PIN) == LOW) {
  // pressed
} else {
  // released
}
```

Remember: with `INPUT_PULLUP`, **`LOW` means pressed.**

## Serial Monitor for debugging

Printing values lets you see what the Arduino is actually reading.

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Freq: ");
  Serial.println(frequency);
}
```

Open it with **Tools → Serial Monitor** and set the baud rate in the bottom corner to **9600**. Use **Tools → Serial Plotter** to see the values as a live graph.

> Printing every loop can flood the monitor. Adding a short `delay(10);` at the end of `loop()` keeps it readable without making the knob feel slow.

## Putting it together (pseudocode)

```
setup:
    buzzer is an output
    button is an input with pull-up
    start Serial

loop:
    read the pot
    convert the reading into a frequency
    if the button is pressed:
        play the frequency
    otherwise:
        stop the sound
    print the values
```

That's the whole program. Turning this into real code is what you'll do in [`03-build-the-circuit.md`](03-build-the-circuit.md).
