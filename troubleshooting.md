# Troubleshooting

Find the problem that matches yours. Most issues are a wire in the wrong row.

**First, always check:**

- Is the USB cable plugged in and the Nano's power LED on?
- Are the 5V and GND jumpers going to the right rails?
- Is every leg in its own row, and not accidentally sharing a row with another part?

---

## The upload fails

- **Tools → Board** should be **Arduino Nano**.
- **Tools → Processor**: switch between **ATmega328P** and **ATmega328P (Old Bootloader)**. Most clone Nanos need the old bootloader.
- **Tools → Port**: unplug the Nano, check the list, plug it back in, and pick the port that appears.
- No port shows up at all? Your Nano may need the **CH340** USB driver. Ask an officer.
- Some USB cables only carry power, not data. Try a different cable.

## No sound at all

1. Run the buzzer test from [Step 3](03-build-the-circuit.md#step-3-wire-the-buzzer). If that's silent, the problem is the buzzer wiring, not your code.
2. Check the buzzer's **+** leg goes to **D8** and **−** goes to GND. Try flipping it.
3. Make sure `BUZZER_PIN` in your code matches the pin you wired.
4. Check the Serial Monitor. If the frequency is printing but there's no sound, it's wiring. If nothing is printing, the code isn't reaching that part.

## The buzzer only makes one pitch

You probably have an **active** buzzer. Quick test: connect it directly between 5V and GND for a second.

- **Beeps on its own** → active buzzer. Swap it for a passive one.
- **Silent or just a click** → passive buzzer (correct). The problem is elsewhere.

Active buzzers often have a sealed bottom. Passive ones often show a green circuit board underneath. That's a good guess, but the 5V test is the sure answer.

## The buzzer plays all the time, even without pressing the button

- With `INPUT_PULLUP`, **`LOW` means pressed**. Check that your `if` says `== LOW`, not `== HIGH`.
- Make sure you call `noTone(BUZZER_PIN);` in the `else` part.
- Check that `pinMode(BUTTON_PIN, INPUT_PULLUP);` is in `setup()`. With plain `INPUT`, the pin "floats" and reads random values.

## The button seems always pressed or never pressed

Four-leg pushbuttons have two pairs of legs that are **always connected inside**. If both of your wires are on the same pair, the button acts like a plain wire.

- Rotate the button 90° and try again, or
- Wire to two legs that are **diagonal** from each other. Diagonal legs are always on opposite sides of the switch.

Make sure the button straddles the center gap of the breadboard.

## The pot reading is stuck or jumpy

| What you see | Likely cause |
|---|---|
| Always `0` | Middle leg isn't on A0, or the 5V leg isn't connected |
| Always `1023` | GND leg isn't connected |
| Random numbers that change without touching the knob | Middle leg isn't connected to A0 at all (the pin is floating) |
| Only uses part of the range | Outer legs aren't on 5V and GND, or the pot is loose |
| Jumps by a few numbers while still | Normal, small noise is expected |

Pots often fit loosely in breadboards. Press it down firmly, or bend the legs slightly so they grip.

## The pitch goes the "wrong" way

Swap the wires on the pot's two outer legs, or swap the last two numbers in `map()`. Either works.

## The pitch changes but sounds choppy or crackly

- Remove or shorten any big `delay()` in `loop()`. With `delay(500)`, the pitch only updates twice a second.
- Lots of `Serial.print()` calls can slow things down. Try a `delay(10)` or print less often.

## `analogWrite()` stopped working on my LED

`tone()` takes over the timer that runs PWM on **D3 and D11**. Move the LED to D5, D6, D9, or D10. (Only matters for the [Going Further](04-going-further.md#challenge-4-led-that-follows-the-pitch) challenges.)

## Still stuck?

- Compare your code with [`solution_code/`](../solution_code/OPS5_pitch_controller_solution/).
- Rebuild one part at a time using the tests in [`03-build-the-circuit.md`](03-build-the-circuit.md).
- Ask an officer. That's what we're here for.
