#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

uint wispProbability = 50;
bool wispActive[] = {false, false, false, false, false, false};
CRGB wispColor[] = {colors[0], colors[1], colors[2], colors[3], colors[4], colors[5]};
uint8_t wispPosition[] = {45, 45, 45, 45, 45, 45};
uint8_t wispDirection[] = {0, 0, 0, 0, 0, 0};
uint8_t wispLife[] = {0, 0, 0, 0, 0, 0};
unsigned long lastMusic;
unsigned long nextMusic;
const uint minMusic = 60000;
const uint maxMusic = 180000;
const uint minWispLife = 30;
const uint maxWispLife = 130;

void setupAttractMode(unsigned long now)
{
  Serial.println("Setup Attract mode...");
  writeLog("Mode: Attract");
  enableButtons();
  for (uint8_t i = 0; i < 6; ++i)
  {
    wispActive[i] = false;
  }
  lastMusic = now;
  nextMusic = random(maxMusic - minMusic) + minMusic;
  visualizeMusic = true;
}

void loopAttractMode(unsigned long now)
{
  // buttons wake up the artifact
  for (uint8_t i = 0; i < 6; ++i)
  {
    if (digitalRead(buttonPins[i]) == LOW)
    {
      disableButtons();
      musicPlaying = false;
      visualizeMusic = false;
      changeMode(MODE_STARTUP, now);
      return;
    }
  }
  EVERY_N_MILLISECONDS(30)
  {
    for (uint8_t i = 0; i < 6; ++i)
    {
      sideLEDs[i].fadeToBlackBy(80);
      topLEDs[i].fadeToBlackBy(80);
    }

    if (!musicPlaying)
    {
      if (now - lastMusic > nextMusic)
      {
        uint8_t attractIndex = random(6);
        lastMusic = now;
        nextMusic = random(maxMusic - minMusic) + minMusic;

        // no wisps during music
        for (uint8_t i = 0; i < 6; ++i)
        {
          wispActive[i] = false;
        }

        playMusic(attractThemes[attractIndex], attractThemeSizes[attractIndex], now);
        return;
      }

      if (random(wispProbability) == 0)
      {
        uint8_t wispIndex = random(6);
        if (wispActive[wispIndex] == false)
        {
          wispActive[wispIndex] = true;
          wispPosition[wispIndex] = 45;
          wispDirection[wispIndex] = random(6);
          wispColor[wispIndex] = colors[random(6)];
          wispLife[wispIndex] = random(maxWispLife - minWispLife) + minWispLife;
        }
      }

      for (uint8_t i = 0; i < 6; ++i)
      {
        if (wispActive[i])
        {
          int8_t nextPosition;
          sideLEDs[i][wispPosition[i]] = wispColor[i];
          nextPosition = sideLinks[wispPosition[i]][wispDirection[i]];
          if (nextPosition == -1)
          {
            wispDirection[i] = (wispDirection[i] + 3) % 6;
            nextPosition = sideLinks[wispPosition[i]][wispDirection[i]];
          }
          wispPosition[i] = nextPosition;
          wispDirection[i] = ((random(3) - 1) + wispDirection[i] + 6) % 6;
          wispLife[i] -= 1;

          if (wispLife[i] == 0)
          {
            wispActive[i] = false;
          }
        }
      }
    }
  }
}