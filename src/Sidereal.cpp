#include <Arduino.h>
#include <FastLED.h>
#include "io.h"
#include "leds.h"
#include "mode.h"
#include "music.h"

void setup()
{
  unsigned long now;
  bool postFlag = false;

  Serial.begin(9600);
  Serial.println("Starting Sidereal...");
  delay(2000);

  setupLEDs();
  setupButtons();

  // check for if we enter POST mode
  delay(1000);

  for (uint8_t i = 0; i < 6; ++i)
  {
    if (digitalRead(buttonPins[i]) == LOW)
    {
      postFlag = true;
    }
  }

  now = millis();
  if (postFlag)
  {
    changeMode(MODE_POST, now);
  }
  else
  {
    changeMode(MODE_STARTUP, now);
  }
}

void loop()
{
  unsigned long now = millis();

  updateMusic(now);
  loopMode(now);
  FastLED.show();
}
