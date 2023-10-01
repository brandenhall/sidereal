#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

void setupWinMode(unsigned long now)
{
    Serial.println("Setup Win mode...");
    writeLog("Mode: Win");
    playMusic(winTheme, winThemeSize, now);
    disableButtons();
}

void loopWinMode(unsigned long now)
{
    EVERY_N_MILLISECONDS(30)
    {
        if (now - modeStartTime < 8000)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                sideLEDs[i].fadeToBlackBy(128);
                topLEDs[i].fadeToBlackBy(128);

                sideLEDs[i][random(91)] = CRGB::White;
                sideLEDs[i][random(91)] = CRGB::White;
                topLEDs[i][random(37)] = CRGB::White;
            }
        }
        else
        {
            changeMode(MODE_DISPENSE, now);
        }
    }
}