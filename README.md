# UltrasonicKeyboardMelodies
This project is closely related to the the [UltrasonicKeyboard](https://github.com/nathanfu88/UltrasonicKeyboard) project. UltrasonicKeyboardMelodies demonstrates how to set up a melody to be played by a piezobuzzer using an Arduino microcontroller.

## Schematic/Circuit
The schematic for this project is nearly identical to the [schematic from UltrasonicKeyboard](https://github.com/nathanfu88/UltrasonicKeyboard/blob/master/schematic.png). The only difference is the exclusion of the HC-SR04 connection. The pins used by the HC-SR04 in UltrasonicKeyboard are not used in this project. Effectively, the same [circuit](https://github.com/nathanfu88/UltrasonicKeyboard/blob/master/breadboard.png) can be used.

## How It Works
We use the same underlying method as the [Arduino ToneMelody sample](https://www.arduino.cc/en/Tutorial/toneMelody). Refer to the sample project for a barebones example of playing a melody using a piezobuzzer.

Instead of a single melody, we define a 2D array of notes, with each subarray a collection of notes for one melody. Another 2D array holds the durations of each of the notes. Being able to play variable note durations enables a much closer representation of the melody if it were played on, say, a piano.

Pauses are introduced between each note emission, as it would be difficult to distinguish different notes otherwise. These pauses also simulate the concept of a "tempo" - longer pauses between notes means the delay between notes is longer. The duration of the pauses with each note (again, for musical timing reasons), so the easiest way to determine the pause durations is experimentally.

The pushbutton section of the circuit rotates through each of the hardcoded melodies, looping back to the first melody when all melodies have been exhausted. A "metronome melody" is played when switching between melodies to make the transition a little smoother.

## How To Use
Open up the [project](melodies/melodies.ino) in Arduino IDE and program your Arduino Nano.