#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

uint startupFrame = 0;
uint8_t startupSideColor = 0;
uint8_t startupSideRing = 0;

void setupStartupMode(unsigned long now)
{
  Serial.println("Setup Startup mode...");
  writeLog("Mode: Startup");
  playMusic(mainTheme, mainThemeSize, now);
  FastLED.clear();
  startupFrame = 0;
  startupSideColor = 0;
  startupSideRing = 0;
  currentLevel = 0;
  disableButtons();
}

void loopStartupMode(unsigned long now)
{
  EVERY_N_MILLISECONDS(30)
  {
    startupFrame += 1;
    for (uint8_t i = 0; i < 6; ++i)
    {
      sideLEDs[i].fadeToBlackBy(180);
      if (startupSideRing < sizeof(sideRingSizes))
      {
        for (uint8_t j = 0; j < sideRingSizes[startupSideRing]; ++j)
        {
          sideLEDs[i][sideRings[startupSideRing][j]] = colors[startupSideColor];
        }
      }
    }
    startupSideRing += 1;
    if (startupSideRing == sizeof(sideRingSizes) * 2)
    {
      startupSideRing = 0;
      startupSideColor = (startupSideColor + 1) % 6;
    }

    if (!musicPlaying)
    {
      changeMode(MODE_SCRAMBLE, now);
    }
  }
}
