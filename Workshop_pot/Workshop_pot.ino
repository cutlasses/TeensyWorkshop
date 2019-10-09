
#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=113,154
AudioEffectFreeverb      freeverb1;      //xy=269,154
AudioOutputAnalog        dac1;           //xy=416,154
AudioConnection          patchCord1(playMem1, freeverb1);
AudioConnection          patchCord2(freeverb1, dac1);
// GUItool: end automatically generated code


#include "AudioSamplePiano_c3_44k.h"  // include the sample data for the piano sound


const int BUTTON_PIN(0);
const int POT1_PIN(A0);
const int POT2_PIN(A1);

Bounce button_bounce( BUTTON_PIN, 5 );     // 5ms debounce time

void setup()
{
  pinMode( BUTTON_PIN, INPUT_PULLUP ); // set the pin mode for the button and enable the pull up resistor inside the Teensy

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
      Serial.println("Button down!");

      playMem1.play( AudioSamplePiano_c3_44k );
    }
    else if( button_bounce.risingEdge() )
    {
      Serial.println("Button up!");
    }
  }

  float pot1_val = analogRead( POT1_PIN ) / 1024.0f;
  freeverb1.roomsize( pot1_val );

  float pot2_val = analogRead( POT2_PIN ) / 1024.0f;
  freeverb1.damping( pot2_val );
  
  Serial.print( pot1_val );
  Serial.print( "\t\t" );
  Serial.println( pot2_val );

  delay(5);
}
