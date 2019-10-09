
#include <Bounce.h>

const int BUTTON_PIN(0);

Bounce button_bounce( BUTTON_PIN, 5 );     // 5ms debounce time

void setup()
{
  pinMode( BUTTON_PIN, INPUT_PULLUP ); // set the pin mode for the button and enable the pull up resistor inside the Teensy

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
    }
    else if( button_bounce.risingEdge() )
    {
      Serial.println("Button up!");
    }
  }
}
