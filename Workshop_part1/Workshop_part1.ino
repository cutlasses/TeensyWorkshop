#include <Audio.h>
#include <Bounce.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "AudioSamplePiano_c3_44k.h"  // include the sample data for the piano sound

const int BUTTON_PIN(0);

Bounce button_bounce( BUTTON_PIN, 5 );     // 5ms debounce time

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=113,154
AudioOutputAnalog        dac1;           //xy=324,155
AudioConnection          patchCord1(playMem1, dac1);
// GUItool: end automatically generated code


void setup()
{
  pinMode( BUTTON_PIN, INPUT_PULLUP ); // set the pin mode for the button and enable the pull up resistor

  AudioMemory(10); // allocate some memory from the teensy audio libary (10 audio blocks)

  Serial.begin(9600);

  Serial.println("Setup complete");
}

void loop()
{
  // has the button state change?
  if( button_bounce.update() )
  {
    // is the button pressed down
    if( button_bounce.fallingEdge() )
    {
      Serial.println("Button down");

      playMem1.play( AudioSamplePiano_c3_44k );
    }
  }
}
