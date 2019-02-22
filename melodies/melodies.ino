#include "pitches.h"

const byte PUSHBUTTON_PIN = 6;    // D6
const byte SPEAKER_PIN = 8;       // D8

// Melodies
const byte TWINKLE = 0;
const byte BEETHOVEN = 1;
const byte MARIO = 2;
const byte MII = 3;

// Max number of notes in the longest melody (for declaring 2D array)
const byte MAX_NOTES = 48;

// notes in the melody:
const int SCORES[][MAX_NOTES] = {
  // Twinkle Twinkle
  { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0 },
  // Beethoven's 5th
  { 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4,
  0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_G4,
  NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_C5, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4,
  NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_G4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_D5 },
  // Super Mario Theme
  { NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5, 0, NOTE_G4,
  0, NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_B4, 0, NOTE_AS4,
  NOTE_A4, NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5, 0, NOTE_E5,
  0, NOTE_C5, NOTE_D5, NOTE_B4 },
  // Mii Channel Theme
  { NOTE_FS4, 0, NOTE_A4, NOTE_CS5, 0, NOTE_A4, 0, NOTE_FS4, NOTE_D4, NOTE_D4,
  NOTE_D4, 0, NOTE_CS4, NOTE_D4, NOTE_FS4, NOTE_A4, NOTE_CS5, 0, NOTE_A4, 0,
  NOTE_FS4, NOTE_E5, NOTE_DS5, NOTE_D5, 0, NOTE_GS4, 0, NOTE_CS5, NOTE_FS4, 0,
  NOTE_CS5, 0, NOTE_GS4, 0, NOTE_CS5, 0, NOTE_GS4, NOTE_FS4, 0, NOTE_E4, 0,
  NOTE_C4, NOTE_C4, NOTE_C4, 0, NOTE_C4, NOTE_C4, NOTE_C4 }
};

// note durations: 1 = whole, 2 = half, 4 = quarter, 8 = eighth note, etc.
// For Mii theme: dotted quarter = 2.66667, or ~3
const byte DURATIONS[][MAX_NOTES] = {
  // Twinkle Twinkle
  { 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8 },
  // Beethoven's 5th
  { 8, 8, 8, 8, 2, 8, 8, 8, 8, 2,
  8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 2, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 2 },
  // Super Mario Theme
  { 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4,
  4, 4, 8, 8, 4, 4, 8, 8, 8, 8, 8, 8,
  4, 6, 6, 6, 4, 8, 8, 8, 8,
  8, 8, 8, 8 },
  // Mii Channel Theme
  { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 2, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 3, 8, 8, 3, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 3, 8, 8, 8 }
};

byte prevButtonState = LOW;
byte melody = 0;

void setup() {
  pinMode(PUSHBUTTON_PIN, INPUT);

  // Start off by playing melody 0
  playMelody(melody);
}

void playMetronome() {
  const byte NUM_TICKS = 4;
  const int TICK_FREQ = 1000;
  const byte TICK_DUR = 10;
  const int TICK_DELAY = 1000;

  for (byte i = 0; i < NUM_TICKS; i++) {
    tone(SPEAKER_PIN, TICK_FREQ, TICK_DUR);
    delay(TICK_DELAY);
  }
}

void playMelody(const byte melody) {
  byte numNotes = 0;
  // Note delay multiplier that affects "tempo" of melody
  // This was experimentally found and tweaked for each melody
  float tempo = 0;

  switch (melody) {
    case TWINKLE:
      numNotes = 32;
      tempo = 3;
      break;
    case BEETHOVEN:
      numNotes = 36;
      tempo = 1.5;
      break;
    case MARIO:
      numNotes = 36;
      tempo = 1.3;
      break;
    case MII:
      numNotes = 48;
      tempo = 1.8;
      break;
    default:
      break;
  }

  playMetronome();

  for (int curNote = 0; curNote < numNotes; curNote++) {
    // To calculate the note duration, take one second divided by the note type.
    // I.E. quarter note = 1000 / 4
    const int noteDuration = 1000 / DURATIONS[melody][curNote];
    tone(SPEAKER_PIN, SCORES[melody][curNote], noteDuration);

    // Insert a delay between each note to establish a "tempo"
    const int pauseBetweenNotes = noteDuration * tempo;
    delay(pauseBetweenNotes);

    // Stop playing
    noTone(SPEAKER_PIN);
  }
}

void loop() {
  // Read pushbutton
  byte newButtonState = digitalRead(PUSHBUTTON_PIN);
  if (newButtonState == HIGH && prevButtonState == LOW) {
    // Loop through melodies and enforce bounds
    if (++melody > MII) {
      melody = TWINKLE;
    }

    playMelody(melody);
  }

  prevButtonState = newButtonState;
}
