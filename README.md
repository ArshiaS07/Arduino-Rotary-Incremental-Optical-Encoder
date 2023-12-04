# Arduino Rotary Encoder Library

The Arduino Rotary Encoder Library is a library for using a rotary incremental optical encoder with an Arduino microcontroller. This library provides a convenient way to interface with the encoder and retrieve count and speed information.

## Features

- Supports rotary incremental optical encoders.
- Provides methods to retrieve the encoder count and speed in degrees per second.
- Uses interrupt-based reading of the encoder signals for accurate counting.
- Optional debug output for monitoring the encoder count and speed through the Serial interface.

## Installation

1. Download the library as a ZIP file from the GitHub repository.
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library.
3. Select the downloaded ZIP file and click "Open".
4. The library is now installed and ready to use.

## Usage

1. Connect the CLK (clock) pin of the rotary encoder to a digital input pin on the Arduino.
2. Connect the DT (data) pin of the rotary encoder to another digital input pin on the Arduino.
3. Create an instance of the `RotaryEncoder` class, passing the CLK and DT pin numbers to the constructor.
4. Call the `begin()` method of the `RotaryEncoder` instance in the `setup()` function of your Arduino sketch.
5. Use the `getCount()` method to retrieve the current count value of the encoder.
6. Use the `getSpeed()` method to retrieve the current speed of the encoder in degrees per second.

```cpp
#include <RotaryEncoder.h>

// Define the CLK and DT pin numbers
const int clkPin = 2;
const int dtPin = 3;

// Create an instance of the RotaryEncoder class
RotaryEncoder encoder(clkPin, dtPin);

void setup() {
  // Initialize the encoder
  encoder.begin();
  // Additional setup code...
}

void loop() {
  // Read the encoder count
  long count = encoder.getCount();
  // Read the encoder speed
  float speed = encoder.getSpeed();
  
  // Do something with the count and speed values...
  
  // Additional loop code...
}
