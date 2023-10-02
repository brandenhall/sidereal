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
  Serial.println("Powering up Sidereal...");
  delay(2000);

  randomSeed(analogRead(A9));
  setupLEDs();
  setupButtons();
  setupLog();
  writeLog("Power On");
  FastLED.clear();
  FastLED.show();

  // check for if we enter POST mode
  Serial.println("Waiting for POST...");
  enableButtons();
  unsigned long postTime = millis();
  while (millis() - postTime < 5000)
  {
    for (uint8_t i = 0; i < 6; ++i)
    {
      if (digitalRead(buttonPins[i]) == LOW)
      {
        postFlag = true;
      }
    }
  }

  disableButtons();
  now = millis();
  if (postFlag)
  {
    changeMode(MODE_POST, now);
  }
  else
  {
    changeMode(MODE_ATTRACT, now);
  }
}

void loop()
{
  unsigned long now = millis();

  updateMusic(now);
  loopMode(now);
  FastLED.show();
}
