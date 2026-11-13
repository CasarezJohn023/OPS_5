/*
  OPS 5: Pitch Perfect (solution)
  TXST IEEE Student Branch

  Hold the button to play a note. Turn the knob to change the pitch.

  Wiring (matches the circuit diagrams):
    Potentiometer: outer legs -> 5V and GND, middle leg (wiper) -> A3
    Piezo buzzer:  + -> D5, - -> GND
    Pushbutton:    one side -> D3, other side -> GND  (uses INPUT_PULLUP)

  Works on an Arduino Uno or Nano; the pin numbers are the same.
*/

// ----- Pins -----
const int POT_PIN    = A3;
const int BUZZER_PIN = 5;
const int BUTTON_PIN = 3;

// ----- Pitch range (Hz) -----
const int MIN_FREQ = 100;
const int MAX_FREQ = 2000;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // released = HIGH, pressed = LOW
  Serial.begin(9600);
}

void loop() {
  // Read the knob (0 - 1023) and turn it into a frequency
  int potValue  = analogRead(POT_PIN);
  int frequency = map(potValue, 0, 1023, MIN_FREQ, MAX_FREQ);

  // Play only while the button is held
  if (digitalRead(BUTTON_PIN) == LOW) {   // pressed
    tone(BUZZER_PIN, frequency);
  } else {                                 // released
    noTone(BUZZER_PIN);
  }

  // Show what the Arduino is reading (Tools -> Serial Monitor, 9600 baud)
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Freq: ");
  Serial.println(frequency);

  delay(10);
}
