#include <MIDIUSB.h>

// app constants
const int DELAY = 10;
const int MAX_ANALOG_VALUE = 1023;
const int MAX_MIDI_VALUE = 127;
const int MAX_LED_BRIGHTNESS = 5;
const int ZERO = 0;
const uint8_t MIDI_CHANNEL = 1;
const int NUM_INPUTS = 6;

// analog input pins
const int x1Input = A0;
const int y1Input = A1;
const int z1Input = A2;
const int x2Input = A3;
const int y2Input = A4;
const int z2Input = A5;

// led pins
const int x1Led = 3;
const int y1Led = 5;
const int z1Led = 6;
const int x2Led = 9;
const int y2Led = 10;
const int z2Led = 11;

// on/off pins
const int onOffSwitch = 12;
const int onOffLed = 4;

// mode pins and consts
const int MODE_A = 0;
const int MODE_B = 1;
const int MODE_C = 2;
const int modePin1 = 7;
const int modePin2 = 8;
bool modePin1On = false;
bool modePin2On = false;
int currentMode = MODE_A;

// store input pins in an array
const int analogInputPins[NUM_INPUTS] = { x1Input, y1Input, z1Input, x2Input, y2Input, z2Input };

// store LED pins in an array
const int ledPins[NUM_INPUTS] = { x1Led, y1Led, z1Led, z2Led, y2Led, x2Led };

// store MIDI values for each input in an array
int midiValues[NUM_INPUTS] = { 0, 0, 0, 0, 0, 0 };

bool on = false;

const int directions[NUM_INPUTS] = { -1, 1, 1, -1, 1, 1 };
const int ledDirections[NUM_INPUTS] = { 1, -1, 1, 1, -1, 1 };

void setup() {

  // uncomment if Serial.println is used
  // Serial.begin(9600);

  for (int i = 0; i < NUM_INPUTS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(onOffSwitch, INPUT_PULLUP);
  pinMode(modePin1, INPUT_PULLUP);
  pinMode(modePin2, INPUT_PULLUP);
}

void loop() {

  // read if on/off switch is on or off
  on = digitalRead(onOffSwitch) == 1;

  // read mode pins
  modePin1On = digitalRead(modePin1);
  modePin2On = digitalRead(modePin2);
  currentMode = modePin1On && !modePin2On ? MODE_A :
    modePin1On && modePin2On ? MODE_B :
    MODE_C;

  if (on) {
    digitalWrite(onOffLed, HIGH);
  } else {
    digitalWrite(onOffLed, LOW);
  }

  // loop through inputs
  for (int i = 0; i < NUM_INPUTS; i++) {

    if (!on) {
      analogWrite(ledPins[i], ZERO);
      continue;
    }

    int analogValue = directions[i] == 1
                        ? analogRead(analogInputPins[i])
                        : map(analogRead(analogInputPins[i]), MAX_ANALOG_VALUE, ZERO, ZERO, MAX_ANALOG_VALUE);

    int midiValue = map(analogValue, ZERO, MAX_ANALOG_VALUE, ZERO, MAX_MIDI_VALUE);


    // if the new MIDI value is different from the previous one,
    // then store the new value and send a control change
    if (abs(midiValue - midiValues[i]) >= 2) {

      // output LED brightness based on analog value
      analogWrite(
        ledPins[i],
        map(
          analogValue,
          ZERO,
          MAX_ANALOG_VALUE,
          ledDirections[i] == -1 ? MAX_LED_BRIGHTNESS : ZERO,
          ledDirections[i] == -1 ? ZERO : MAX_LED_BRIGHTNESS));


      midiValues[i] = midiValue;
      sendControlChange(MIDI_CHANNEL, i + 1, midiValue);
      MidiUSB.flush();
    }
  }


  delay(DELAY);
}

midiEventPacket_t event;
void sendControlChange(uint8_t channel, uint8_t control, uint8_t value) {

  // midiEventPacket_t event = { 0x0B, 0xB0 | (channel - 1), control, value };
  MidiUSB.sendMIDI({ 0x0B, 0xB0 | (channel - 1), control, value });
}
