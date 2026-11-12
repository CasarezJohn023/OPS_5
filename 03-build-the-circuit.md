# 03: Build the Circuit

Time to build it. Wire one part at a time and test as you go. It's much easier to find a mistake in one part than in the whole board.

> **Unplug the USB cable while you're wiring.** Plug it back in only when you're ready to upload or test.

## Wiring table

| Part | Pin |
|---|---|
| Potentiometer left leg | 5V |
| Potentiometer middle leg (wiper) | A0 |
| Potentiometer right leg | GND |
| Buzzer + | D8 |
| Buzzer − | GND |
| Pushbutton (one side) | D2 |
| Pushbutton (other side) | GND |
| Optional indicator LED | D13 → LED long leg, short leg → 220 Ω → GND |

## Step 1: Place the Nano and set up the power rails

1. Push the Nano into the breadboard so it straddles the center gap, with the USB port hanging off one end.
2. Run a jumper from the Nano's **5V** pin to the breadboard's **+** rail.
3. Run a jumper from a Nano **GND** pin to the **−** rail.

Every part below gets its 5 V or GND from these rails.

## Step 2: Wire the potentiometer

1. Push the pot into the breadboard so each of its three legs is in a different row.
2. **Left leg** → **+** rail (5 V).
3. **Right leg** → **−** rail (GND).
4. **Middle leg** → **A0**.

### Test it

Upload this small test sketch:

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
  delay(50);
}
```

Open the Serial Monitor at 9600 baud and turn the knob. You should see the number move smoothly from about 0 to 1023. If it doesn't, check [troubleshooting](troubleshooting.md#the-pot-reading-is-stuck-or-jumpy) before moving on.

## Step 3: Wire the buzzer

1. Place the buzzer so its two legs are in different rows.
2. **+ leg** (longer leg, or marked `+`) → **D8**.
3. **− leg** → **−** rail (GND).

> Too loud? Put a 100 Ω resistor between D8 and the buzzer's + leg.

### Test it

```cpp
void setup() {
  tone(8, 440, 1000);   // play A for 1 second
}

void loop() {}
```

You should hear one steady beep after uploading. Press the Nano's reset button to hear it again.

## Step 4: Wire the button

1. Place the pushbutton across the center gap so its legs land in different rows.
2. One leg → **D2**.
3. The leg on the **opposite side** → **−** rail (GND).

No resistor needed. The code turns on the Nano's internal pull-up.

> Four-leg buttons have two pairs of legs that are always connected. If the button seems "always pressed," rotate it 90° (see [troubleshooting](troubleshooting.md#the-button-seems-always-pressed-or-never-pressed)).

## Step 5 (optional): Indicator LED

1. LED **long leg** → **D13**.
2. LED **short leg** → 220 Ω resistor → **−** rail.

The Nano also has a built-in LED on D13, so even without wiring one you'll see it light up.

## Step 6: Write the program

Open [`starter_code/OPS5_pitch_controller_starter/`](../starter_code/OPS5_pitch_controller_starter/) in the Arduino IDE. Work through each `TODO`:

### TODO 1: Name the pins

```cpp
const int POT_PIN    = A0;
const int BUZZER_PIN = 8;
const int BUTTON_PIN = 2;
const int LED_PIN    = 13;   // optional
```

### TODO 2: Choose a frequency range

```cpp
const int MIN_FREQ = 100;
const int MAX_FREQ = 2000;
```

Feel free to change these later. Try 200–1000 for something less piercing.

### TODO 3: Set up the pins and Serial in `setup()`

```cpp
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}
```

### TODO 4: Read the knob and convert it to a frequency

```cpp
int potValue  = analogRead(POT_PIN);
int frequency = map(potValue, 0, 1023, MIN_FREQ, MAX_FREQ);
```

### TODO 5: Play or stop based on the button

```cpp
if (digitalRead(BUTTON_PIN) == LOW) {   // pressed
  tone(BUZZER_PIN, frequency);
  digitalWrite(LED_PIN, HIGH);
} else {                                 // released
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
}
```

### TODO 6: Print the values

```cpp
Serial.print("Pot: ");
Serial.print(potValue);
Serial.print("  Freq: ");
Serial.println(frequency);

delay(10);
```

## Step 7: Upload and test

1. Plug in the USB cable.
2. **Tools → Board → Arduino Nano**.
3. **Tools → Processor**: if the upload fails, try **ATmega328P (Old Bootloader)**.
4. **Tools → Port**: pick the port that shows up when the Nano is plugged in.
5. Click **Upload**.

### Checklist

- [ ] Silent when the button is released
- [ ] Plays a tone while the button is held
- [ ] Pitch slides up and down when you turn the knob while holding the button
- [ ] Sound stops right away when you let go
- [ ] Serial Monitor shows the pot value and frequency changing

All checked? You built an instrument. Head to [`04-going-further.md`](04-going-further.md) to make it play real notes. Something not working? See [`troubleshooting.md`](troubleshooting.md), or compare against [`solution_code/`](../solution_code/OPS5_pitch_controller_solution/).
