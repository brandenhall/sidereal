#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

uint8_t topRingIndex = 0;
uint8_t sideRingIndex = 0;

void setupSolveMode(unsigned long now)
{
    Serial.println("Setup Solve mode...");
    writeLog("Mode: Solve");
    playMusic(solveTheme, solveThemeSize, now);
    disableButtons();
    topRingIndex = 0;
    sideRingIndex = 0;
}

void loopSolveMode(unsigned long now)
{
    if (now - modeStartTime < 3000)
    {
        EVERY_N_MILLISECONDS(60)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                topLEDs[i].fadeToBlackBy(128);
                sideLEDs[i].fadeToBlackBy(128);
                if (topRingIndex < 4)
                {
                    for (uint8_t j = 0; j < topRingSizes[topRingIndex]; ++j)
                    {
                        topLEDs[i][topRings[topRingIndex][j]] = CRGB::White;
                    }
                }

                if (sideRingIndex < 6)
                {
                    for (uint8_t j = 0; j < sideRingSizes[sideRingIndex]; ++j)
                    {
                        sideLEDs[i][sideRings[sideRingIndex][j]] = CRGB::White;
                    }
                }
            }
            topRingIndex += 1;
            sideRingIndex += 1;
        }
    }
    else
    {
        currentLevel += 1;
        changeMode(MODE_SCRAMBLE, now);
    }
}