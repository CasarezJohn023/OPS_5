# 04: Going Further

Got the basic version working? Try these challenges. They're roughly in order from easiest to hardest. Each one has a hint, but try it yourself first.

## Challenge 1: Change the feel

Small changes to try before writing anything new:

- Make the range narrower (for example 200–800 Hz). Is it easier to land on a pitch you want?
- Flip the direction so turning clockwise lowers the pitch.
- Try very low frequencies like 31–100 Hz. What does the buzzer sound like down there?

<details>
<summary>Hint</summary>

All of these are changes to the two numbers at the end of `map()`. Swapping them reverses the direction.
</details>

## Challenge 2: Snap to real musical notes

Right now the pitch slides smoothly. Make the knob jump between real notes instead, like the keys on a piano.

Here's one octave of the C major scale (C4 to C5):

| Note | C | D | E | F | G | A | B | C |
|---|---|---|---|---|---|---|---|---|
| Hz | 262 | 294 | 330 | 349 | 392 | 440 | 494 | 523 |

<details>
<summary>Hint</summary>

Store the frequencies in an array, then use `map()` to choose an **index** into the array instead of a frequency.

```cpp
const int NOTES[] = {262, 294, 330, 349, 392, 440, 494, 523};
const int NUM_NOTES = 8;

int index = map(potValue, 0, 1024, 0, NUM_NOTES);
int frequency = NOTES[index];
```

Using `1024` (not `1023`) as the top of the input range makes the last note as easy to reach as the others. Since `analogRead()` never returns 1024, `index` stays between 0 and 7.
</details>

## Challenge 3: Octave button

Add a second button on **D3** (wired the same way as the first). Each press moves the instrument up one octave. After the top octave, it wraps back to the bottom.

<details>
<summary>Hint</summary>

Going up one octave **doubles** the frequency. Keep a variable like `int octave = 0;` and multiply: `frequency * (1 << octave)`, where `1 << octave` is 1, 2, 4, ...

You only want to change the octave once per press, not every time `loop()` runs while the button is held. Remember the button's state from the last loop, and only act when it goes from `HIGH` to `LOW`:

```cpp
bool lastOctaveButton = HIGH;

// inside loop():
bool now = digitalRead(OCTAVE_PIN);
if (lastOctaveButton == HIGH && now == LOW) {
  octave = (octave + 1) % 3;
  delay(20);   // simple debounce
}
lastOctaveButton = now;
```
</details>

## Challenge 4: LED that follows the pitch

Add an LED (with a 220 Ω resistor) whose brightness rises and falls with the pitch.

<details>
<summary>Hint</summary>

Use `analogWrite(pin, 0–255)` on a PWM pin, and `map()` the frequency into 0–255.

**Watch out:** `tone()` takes over the timer that runs PWM on **D3 and D11**, so use **D5, D6, D9, or D10** for this LED. If you did Challenge 3, your octave button is on D3, which is fine because buttons don't use PWM.
</details>

## Challenge 5: Play a melody

When the button is **double-pressed** (two presses within about 400 ms), play a short tune instead of the knob pitch.

<details>
<summary>Hint</summary>

Store the melody as two arrays: one for frequencies, one for durations.

```cpp
const int MELODY[]    = {262, 262, 392, 392, 440, 440, 392};
const int DURATIONS[] = {300, 300, 300, 300, 300, 300, 600};
```

Play each note with `tone(BUZZER_PIN, MELODY[i], DURATIONS[i]);` then `delay(DURATIONS[i] * 1.3);` so there's a small gap between notes.

To detect a double-press, use `millis()` to record the time of each press. If the new press comes less than 400 ms after the last one, it's a double-press.
</details>

## Challenge 6: Bring back the state machine

In OPS 4 you used an `enum` and `switch` to manage a traffic light. Use the same idea here with modes like:

```cpp
enum Mode { SLIDE, NOTES, MELODY };
```

A long press (hold for 1 second) could switch modes, and a short press plays sound in the current mode.

<details>
<summary>Hint</summary>

Use `millis()` to measure how long the button was held. Record the time when it's pressed, and when it's released, check whether more than 1000 ms passed.
</details>

## Share it

Built something cool? Show it to an officer, or open a pull request with your sketch in a new folder.
