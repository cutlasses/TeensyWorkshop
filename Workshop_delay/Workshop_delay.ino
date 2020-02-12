
#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=74,230
AudioMixer4              mixer1;         //xy=244,54
AudioEffectDelay         delay1;         //xy=381,170
AudioMixer4              mixer2;         //xy=516,356
AudioOutputAnalog        dac1;           //xy=700,355
AudioConnection          patchCord1(playMem1, 0, mixer1, 1);
AudioConnection          patchCord2(playMem1, 0, mixer2, 1);
AudioConnection          patchCord3(mixer1, delay1);
AudioConnection          patchCord4(delay1, 0, mixer1, 0);
AudioConnection          patchCord5(delay1, 0, mixer2, 0);
AudioConnection          patchCord6(mixer2, dac1);
// GUItool: end automatically generated code



#include "AudioSamplePiano_c3_44k.h"  // include the sample data for the piano sound


const int BUTTON_PIN(0);
const int POT1_PIN(A0);
const int POT2_PIN(A1);

Bounce button_bounce( BUTTON_PIN, 5 );     // 5ms debounce time

void setup()
{
  pinMode( BUTTON_PIN, INPUT_PULLUP ); // set the pin mode for the button and enable the pull up resistor inside the Teensy

  AudioMemory(128); // allocate some memory from the teensy audio libary

  Serial.begin(9600);

  Serial.println("Setup complete");

  // mix dry and wet signal (50% of each)
  mixer2.gain( 0, 0.5f ); // wet
  mixer2.gain( 1, 0.5f ); // dry
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

  const int min_delay_time = 50;
  const int max_delay_time = 300;
  
  static float old_pot1_val_raw = 0;
  float pot1_val_raw = analogRead( POT1_PIN );

  // is the difference large enough to change the delay time?
  if( abs( old_pot1_val_raw - pot1_val_raw ) > 50 )
  {
    const float pot1_val = pot1_val_raw / 1024.0f;
    const float delay_time = min_delay_time + ( max_delay_time * pot1_val );
    delay1.delay( 0, delay_time );
    Serial.println(delay_time);
    
    // update the old value
    old_pot1_val_raw = pot1_val_raw;
  }

  float pot2_val = analogRead( POT2_PIN ) / 1024.0f;
  mixer1.gain( 0, pot2_val ); // feedback
  mixer1.gain( 1, 1.0f );     // source audio
  
  //Serial.print( old_pot1_val_raw / 1024.0f );
  //Serial.print( "\t\t" );
  //Serial.println( pot2_val );

  delay(5);
}
