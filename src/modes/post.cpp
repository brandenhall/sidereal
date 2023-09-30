#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../music.h"

uint8_t postStep = 0;
uint8_t postColor = 0;
uint8_t postMallet = 0;
unsigned long postTime = 0;
bool postDebounce[6] = {false, false, false, false, false, false};

void testFacet(uint8_t facet, unsigned long now)
{
  if (now - postTime > 1000)
  {
    postTime = now;
    postColor = (postColor + 1) % 3;
  }

  for (uint8_t i = 0; i < 6; ++i)
  {
    CRGB color = CRGB::Black;

    if (i == facet)
    {
      if (postColor == 0)
      {
        color = CRGB::Red;
      }
      else if (postColor == 1)
      {
        color = CRGB::Green;
      }
      else if (postColor == 2)
      {
        color = CRGB::Blue;
      }
    }
    fill_solid(sideLEDs[i], NUM_SIDE_LEDS, color);
    fill_solid(topLEDs[i], NUM_TOP_LEDS, color);
  }
}

void testDrum(unsigned long now)
{
  if (now - postTime > 1000)
  {
    postTime = now;
    swingMallet(postMallet, now);
    postMallet = (postMallet + 1) % 8;
  }
}

void testPrizeRelease(unsigned long now)
{
  digitalWrite(prizeReleasePin, HIGH);
  delay(2000);
  digitalWrite(prizeReleasePin, LOW);
  postTime = millis();
  postStep = (postStep + 1) % 8;
}

void setupPostMode(unsigned long now)
{
  Serial.println("Setup POST mode...");
  enableButtons();
  for (uint8_t i = 0; i < 6; ++i)
  {
    CRGB color = CRGB::Black;
    fill_solid(sideLEDs[i], NUM_SIDE_LEDS, color);
    fill_solid(topLEDs[i], NUM_TOP_LEDS, color);
  }
}

void loopPostMode(unsigned long now)
{
  uint8_t buttonState;

  switch (postStep)
  {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    testFacet(postStep, now);
    break;
  case 6:
    testDrum(now);
    break;
  case 7:
    testPrizeRelease(now);
    break;
  }

  // check buttons to see if we can move on to next step
  for (uint8_t i = 0; i < 6; ++i)
  {
    buttonState = digitalRead(buttonPins[i]);
    if (postDebounce[i] && buttonState == HIGH)
    {
      postDebounce[i] = false;
    }
    else if (!postDebounce[i] && buttonsActive && buttonState == LOW)
    {
      postDebounce[i] = true;
      postTime = now;
      postStep = (postStep + 1) % 8;
      Serial.print("POST Step: ");
      Serial.println(postStep);

      // if testing drum or prize release clear the LEDs
      if (postStep > 5)
      {
        for (uint8_t j = 0; j < 6; ++j)
        {
          CRGB color = CRGB::Black;
          fill_solid(sideLEDs[j], NUM_SIDE_LEDS, color);
          fill_solid(topLEDs[j], NUM_TOP_LEDS, color);
        }
      }
      break;
    }
  }
}