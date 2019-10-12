#include <Audio.h>
#include <Bounce.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int BUTTON_PIN(0);

Bounce button_bounce( BUTTON_PIN, 5 );     // 5ms debounce time

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
    }
  }
}
